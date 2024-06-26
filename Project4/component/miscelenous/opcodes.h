//
// Created by user on 2024-04-22.
//

#ifndef COMPUTER_ARCHITECTURE_OPCODES_H
#define COMPUTER_ARCHITECTURE_OPCODES_H
enum _opcode{R = 0x0,
    ADDI = 0x8, ADDIU = 0x9,
    ANDI = 0xC,
    BEQ = 0x4, BNE = 0x5,
    J = 0x2, JAL = 0x3,
    // LBU = 0x24, LHU = 0x25,
    // LL = 0x30,
    LUI = 0xF,
    LW = 0x23, ORI = 0xd,
    SLTI = 0xA, SLTIU = 0xb,
    // SB = 0x28, SC = 0x38, SH = 0x29,
    SW = 0x2b
}Opcodes_enum;
#endif //COMPUTER_ARCHITECTURE_OPCODES_H
