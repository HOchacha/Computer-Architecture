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

uint32_t number_of_instructions = 0;
uint32_t number_R_type = 0;
uint32_t number_I_type = 0;
uint32_t number_J_type = 0;
uint32_t number_memory_access = 0;
uint32_t number_branch = 0;
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

    // load program in memory
    // start from 0x0
    freopen("output.txt", "w",stdout);
    uint32_t buff;
    PC = 0x00000000;
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
    fclose(file);

    // initializing register $ra register and $sp
    general_reg.reg[$ra] = 0xFFFFFFFF;
    general_reg.reg[$sp] = 0x01000000;


    // start single cycle machine
    while(0xFFFFFFFF != PC) {

// fetch instruction
        if(PC == 0xd0){
            printf("ASd");
        }
        // this instruction fetch an instruction and increases PC value by 4
        uint32_t instruction = fetch_instruction(PC);
        PC += 4;

// fetch instruction log
#ifdef LOG
        printf("Instruction : %08x\n", instruction);
#endif

        //PIPELINE IF LATCH ACCESS
        /* leave a space for further implementation */

// decode instruction

        // get the decoded values from instruction (opcode, rs, rt, rd, shamt, funct, imm, s_imm, j_addr
        Decoded_values decoded = decode_instruction(instruction);

        // get control signal from control unit
        CU_input cu_opcode = {decoded.opcode, decoded.funct};
        CU_output control;
        control = set_control_signal(cu_opcode);

// access register

        // this returns naive register values whatever opcode is
        Reg_out operands = get_value_from_decoded_values(decoded, control);

        //PIPELINE ID LATCH ACCESS
        /* leave a space for further implementation */

// execute instruction & Branch Arithmetic Operation

        Alu_control alu_control = get_ALU_operation(decoded.funct,control, decoded.opcode);

        // determine which value proper for operand2
        Alu_input alu_inputs = {0,};
        alu_inputs.operand1 = alu_control.isShift ? operands.reg2 : operands.reg1;
        alu_inputs.operand2 = control.ALU_src ? decoded.s_immediate : operands.reg2;
        alu_inputs.operand2 = alu_control.isShift ? decoded.shamt : alu_inputs.operand2;
        alu_inputs.operand2 = control.isZeroExtend ? decoded.imm : alu_inputs.operand2;
        // execute operands
        Alu_output alu_output = do_arithmetic_operation(alu_inputs,alu_control);

// Branch and Jump Processing

        uint32_t shift_left2_s_imm = decoded.s_immediate << 2;
        uint32_t branch_addr = PC + shift_left2_s_imm;

        uint32_t jump_temp = decoded.j_address << 2;
        uint32_t jump_addr = (PC & 0x80000000) | jump_temp;

        uint32_t jump_register = operands.reg1;

        uint32_t isBranch = alu_output.isBranch && (control.isBNE || control.isBEQ);

        //PIPELINE ID LATCH ACCESS
        /* leave a space for further implementation */

// access memory

        Memory_input mem_input = {alu_output.ALUresult, operands.reg2};
        Memory_control mem_control = {control.mem_read, control.mem_write};
        Memory_output mem_output = set_input_memory_and_return_data(mem_input, mem_control);

        uint32_t data_path_to_register = (control.mem_to_reg) ? mem_output.read_data : alu_output.ALUresult;
        data_path_to_register = (control.set_ra) ? PC+4 : data_path_to_register;

// write back result

        // setting access register address
        uint32_t write_register_address = control.isItype ? decoded.rt : decoded.rd;
        write_register_address = control.set_ra ? 31 : write_register_address;

        // write back register
        set_register_from_input(data_path_to_register, write_register_address,control.reg_write, control.isUpperAccess);

        // updating_pc
        uint32_t PC_temp = PC;
        PC_temp = isBranch ? branch_addr : PC_temp;
        PC_temp = control.jump ? jump_addr : PC_temp;
        PC_temp = control.isJR ? jump_register : PC_temp;
        PC = PC_temp;
        //print_registers();
    }

    // prolog: print out all the information
    printf("=============result=======repr in hex==========\n");
    printf("%-40s: %6d\n","Final return Value register[v0]", general_reg.reg[2]);
    printf("%-40s: %6d\n", "Number of executed instructions", number_of_instructions);
    printf("%-40s: %6d\n", "Number of executed R-type", number_R_type);
    printf("%-40s: %6d\n", "Number of executed I-type", number_I_type);
    printf("%-40s: %6d\n", "Number of executed J-type", number_J_type);
    printf("%-40s: %6d\n", "Number of memory access instruction", number_memory_access);
    printf("%-40s: %6d\n", "Number of taken branches", number_branch);
    fclose(stdout);
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