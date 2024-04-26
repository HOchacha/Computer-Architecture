//
// Created by user on 2024-04-02.
//
#define LOG

#ifndef STANDARD_HEADER
#define STANDARD_HEADER
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#endif

#ifndef COMPONENT
#define COMPONENT
#include "component/register/register.h"
#include "component/control_unit/control_unit.h"
#include "component/alu/alu.h"
#include "component/memory/memory.h"
#endif

#ifndef SINGLE_CYCLE
#define SINGLE_CYCLE
#include "single_cycle/decode/decode_instruction.h"
#include "single_cycle/execute/execute_instruction.h"
#include "single_cycle/fetch/fetch_instruction.h"
#include "single_cycle/writeback/write_back_instruction.h"
#endif

#define REGISTER_LOG


//init global variable
Register general_reg;

//memory has 0x8000000 byte. make sure a pointer for giving 32 bits into memory
//just recommend to use memory manipulating function
Memory memory;


uint32_t PC;

void print_registers();

int main(int arg, char* args[]) {
    setbuf(stdout, 0);
    if (arg <= 1) {
#ifdef LOG
        printf("no specified argument for program input\n");
#endif
        return -1;
    }

    FILE* file = fopen(args[1], "rb");
    if (file == NULL) {
#ifdef LOG
        printf("Cannot Open the specified file\n");
#endif
    }

    uint32_t buff;
    PC = 0x00000000;
    // currently global variable just work as local varible
    uint32_t PC_loading_temp = PC;
    while (fread(&buff, sizeof(uint32_t), 1, file) == 1) {
        uint32_t upp = (buff << 24) & 0xff000000;
        uint32_t upp2 = (buff << 8) & 0x00ff0000;
        uint32_t upp3 = (buff >> 8) & 0x0000ff00;
        uint32_t upp4 = (buff >> 24) & 0x000000ff;
        uint32_t inst = upp | upp2 | upp3 | upp4;
        *((uint32_t*)(memory.mem + PC_loading_temp)) = inst;
        printf("%08x\n", inst);
        PC_loading_temp+=4;
    }
    printf("PC_LOADING_TEMP : %08x\n", PC_loading_temp);
    // TODO: 메모리 구성 문제 해결
    fclose(file);

    // initializing register $ra register and $sp
    general_reg.reg[$ra] = 0xFFFFFFFF;
    general_reg.reg[$sp] = 0x01000000;

// Start Single Cycle
    // 탈출 조건 명시 $ra 값이 -1이 되면 종료, $31번에 탈출 주소가 명시되어 있음
    while(0xFFFFFFFF != PC) {
        // fetch instruction
        // this instruction fetch an instruction and increases PC value by 4
        uint32_t instruction = fetch_instruction(PC);
#ifdef LOG
        printf("Instruction : %08x\n", instruction);
#endif
        // TODO: remove update PC and make sure it follows desired intention.
        PC += 4;

        //PIPELINE IF LATCH ACCESS
        /* some of the code */

        // decode instruction
        // TODO : Wrap it all of the decoded step into single function
        Decoded_values decoded = decode_instruction(instruction);

        CU_input cu_opcode = {decoded.opcode, decoded.funct};
        CU_output control;
        control = set_control_signal(cu_opcode);

        // access register
        // get_value_from_decoded_values gives the final values of the operands.
        // this returns naive register values whatever opcode is.
        // Also, there is included for determining what register value have to be return regardless of Instruction Type
        // if you reconstruct the code structure, take a look of another function
        Reg_out operands = get_value_from_decoded_values(decoded, control);


        //PIPELINE ID LATCH ACCESS
        /* some of the code */

        // execute instruction & Branch Arithmetic Operation\
    // TODO : Wrap it all of the execute and branch step into single function
        Alu_control alu_control = get_ALU_operation(decoded.funct,control);
        // Reg_out, s_imm
        Alu_input alu_inputs = {0,};
        alu_inputs.operand1 = operands.reg1;
        alu_inputs.operand2 = control.ALU_src ? decoded.s_immediate : operands.reg2;
        alu_inputs.operand2 = alu_control.isShift ? decoded.shamt : alu_inputs.operand2;

        Alu_output alu_output = do_arithmetic_operation(alu_inputs,alu_control);

        // Branch and Jump Processing

        uint32_t shift_left2_s_imm = decoded.s_immediate << 2;
        uint32_t branch_addr = PC + shift_left2_s_imm;

        uint32_t jump_temp = decoded.j_address << 2;
        uint32_t jump_addr = (PC & 0x80000000) | jump_temp;

        uint32_t jump_register = operands.reg1;

        uint32_t isBranch = alu_output.isBranch && (control.isBNE || control.isBEQ);

        //PIPELINE ID LATCH ACCESS
        /* some of the code */

        // access memory
        // TODO: wrap it.
        // access_memory();
        Memory_input mem_input = {alu_output.ALUresult, operands.reg2};
        Memory_control mem_control = {control.mem_read, control.mem_write};
        Memory_output mem_output = set_input_memory_and_return_data(mem_input, mem_control);
        //mux
        uint32_t data_path_to_register = (control.mem_to_reg) ? mem_output.read_data : alu_output.ALUresult;

        // write back result
        // TODO: wrap it.
        // write_back();

        uint32_t write_register_address = control.isItype ? decoded.rt : decoded.rd;
        set_register_from_input(data_path_to_register, write_register_address,control.reg_write);

        // updating_pc
        uint32_t PC_temp = PC;
        PC_temp = isBranch ? branch_addr : PC_temp;
        PC_temp = control.jump ? jump_addr : PC_temp;
        PC_temp = control.isJR ? jump_register : PC_temp;
        PC = PC_temp;
        //print_registers();
    }

    // Some of the processing logic in program

    printf("mem[0x00FFFFE4] = %08x\n", get_memory_value_from_input(0x00FFFFE4));
    // TODO: the end of the program, machine have to set v0 value
    //       the value of the register must be printed out
    //       i. Final return value (value in r2) – up to here, basic requirement
    //       ii. Number of executed instructions
    //       iii. Number of (executed) R-type instruction
    //       iv. Number of I-type instruction
    //       v. Number of J-type instruction
    //       vi. Number of memory access instructions
    //       vii. Number of taken branches
    printf("reg[v0] : %08x\n", general_reg.reg[2]);

    return 0;
}

void print_registers() {
    printf("Register values:\n");
    for (int i = 0; i < 32; i++) {  // 레지스터 32개 모두를 반복
        printf("R%d = %08X\t", i, general_reg.reg[i]);  // 탭을 사용하여 가로로 공간을 만듦
        if ((i + 1) % 4 == 0) {  // 새로운 줄을 위해 매 8개의 레지스터 후에 줄바꿈을 추가
            printf("\n");
        }
    }
    printf("\n\n\n");
}