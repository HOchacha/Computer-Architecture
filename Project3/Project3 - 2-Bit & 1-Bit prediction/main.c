#define LOG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "component/register/register.h"
#include "component/control_unit/control_unit.h"
#include "component/alu/alu.h"
#include "component/memory/memory.h"

#include "single_cycle/decode/decode_instruction.h"
#include "single_cycle/decode/decode_pipe.h"
#include "single_cycle/execute/execute_instruction.h"
#include "single_cycle/fetch/fetch_instruction.h"
#include "single_cycle/writeback/write_back_instruction.h"

#include "util/utils.h"
#include "single_cycle/memory_access/memory_access.h"
#include "component/last_branch_prediction/last_branch_predictor.h"

#define REGISTER_LOG
#define ONLY_RESULT

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
uint32_t prediction_hit = 0;
uint32_t prediction_miss = 0;
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
        return -1;
    }

    // load program in memory
    // start from 0x0
    uint32_t buff;
    uint32_t PC_loading_temp = PC;

    freopen("output.txt", "w",stdout);
#ifdef ONLY_RESULT
    fclose(stdout);
#endif

    PC = 0x00000000;
    while (fread(&buff, sizeof(uint32_t), 1, file) == 1) {

        uint32_t inst = byte_ordering(buff);

        *((uint32_t*)(memory.mem + PC_loading_temp)) = inst;
        printf("%08x\n", inst);
        PC_loading_temp+=4;

    }
    fclose(file);

    if(PC == 0x38C4){
        freopen("output.txt", "w",stdout);
    }
    // initializing register $ra register and $sp
    general_reg.reg[$ra] = 0xFFFFFFFF;
    general_reg.reg[$sp] = 0x01000000;

    uint32_t number_of_cycle = 0;
    IF_ID_LATCH if_id_latch = {0,};
    ID_EX_LATCH id_ex_latch = {0,};
    EX_MEM_LATCH ex_mem_latch = {0,};
    MEM_WB_LATCH mem_wb_latch = {0,};
    uint32_t TERMINATION = 0;


    branch_target_buffer btb = {0};
// start single cycle machine
    while(1) {
        printf("PC : %08X\n", PC);
        number_of_cycle++;

// write back result

        uint32_t current_wb_pc = write_back_pipe(conditional_latch_out_MEM_WB(&mem_wb_latch));



// fetch instruction

        IF_ID_SLOT if_id_slot = fetch_instruction_pipe(PC, TERMINATION, &btb);

        //PIPELINE IF LATCH ACCESS
        push_IF_ID_LATCH(&if_id_latch, if_id_slot);

// decode instruction
// access register

        ID_EX_SLOT id_ex_slot = decode_instruction_pipe(conditional_latch_out_IF_ID(&if_id_latch));

        //PIPELINE ID LATCH ACCESS
        push_ID_EX_LATCH(&id_ex_latch, id_ex_slot);


// execute instruction & Branch Arithmetic Operation
// Branch and Jump Address Processing

        EX_MEM_SLOT ex_mem_slot = execute_instruction_pipe(conditional_latch_out_ID_EX(&id_ex_latch),
                                                           conditional_latch_out_EX_MEM(&ex_mem_latch),
                                                           conditional_latch_out_MEM_WB(&mem_wb_latch),
                                                           &if_id_latch,
                                                           &id_ex_latch,
                                                           &TERMINATION,
                                                           &btb);

        //PIPELINE EX LATCH ACCESS
        push_EX_MEM_LATCH(&ex_mem_latch, ex_mem_slot);

// access memory

        MEM_WB_SLOT mem_wb_slot = memory_access_pipe(conditional_latch_out_EX_MEM(&ex_mem_latch));

        //PIPELINE MEM LATCH ACCESS
        push_MEM_WB_LATCH(&mem_wb_latch, mem_wb_slot);

#ifdef ONLY_RESULT
        freopen("output.txt", "w",stdout);
#endif

//flush latch
        printf("================current pipeline status=================\n");
        printf("IF  res : PC = %08X\n", if_id_latch.slot[OUT_LATCH].current_pc);
        printf("ID  res : PC = %08X\n", id_ex_latch.slot[OUT_LATCH].current_pc);
        printf("EX  res : PC = %08X\n", ex_mem_latch.slot[OUT_LATCH].current_pc);
        printf("MEM res : PC = %08X\n", mem_wb_latch.slot[OUT_LATCH].current_pc);
        printf("WB  res : PC = %08X\n", current_wb_pc);

        flush_IF_ID_LATCH((&if_id_latch));
        flush_ID_EX_LATCH((&id_ex_latch));
        flush_EX_MEM_LATCH((&ex_mem_latch));
        flush_MEM_WB_LATCH((&mem_wb_latch));


#ifdef REGISTER_LOG
        print_registers();
#endif
        if(PC == 0xFFFFFFFF && TERMINATION == 1){
            if(if_id_latch.slot[IN_LATCH].invalid == 1 &&
               id_ex_latch.slot[IN_LATCH].invalid == 1 &&
               ex_mem_latch.slot[IN_LATCH].invalid == 1 &&
               mem_wb_latch.slot[IN_LATCH].invalid == 1){
                break;
            }
        }
    }



    printf("=============result: repr in decimal=================\n");
    printf("%-40s: %6d\n","Final return Value register[v0]", general_reg.reg[2]);
    printf("%-40s: %6d\n", "Number of cycles", number_of_cycle);
    printf("%-40s: %6d\n", "Number of executed instructions", number_of_instructions);
    printf("%-40s: %6d\n", "Number of executed R-type", number_R_type);
    printf("%-40s: %6d\n", "Number of executed I-type", number_I_type);
    printf("%-40s: %6d\n", "Number of executed J-type", number_J_type);
    printf("%-40s: %6d\n", "Number of memory access instruction", number_memory_access);
    printf("%-40s: %6d\n", "Number of taken branches", number_branch);
    printf("%-40s: %6d\n", "Number of branch prediction miss", prediction_miss);
    fclose(stdout);
    return 0;
}

void print_registers() {
    printf("Register values:\n");
    for (int i = 0; i < 32; i++) {
        printf("R%d = %08X\t", i, general_reg.reg[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    printf("\n\n\n");
}