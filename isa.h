#pragma once
/* ISA */
enum {
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};

uint16_t sign_extend(uint16_t low, uint16_t len);

void update_flags(uint16_t rx);

void op_ADD(uint16_t instc);

void op_AND(uint16_t instc);

void op_LDI(uint16_t instc);

void op_BR(uint16_t instc);

void op_JR(uint16_t instc);

void op_JSR(uint16_t instc);

void op_LD(uint16_t instc);

void op_LDR(uint16_t instc);

void op_LEA(uint16_t instc);

void op_NOT(uint16_t instc);

void op_RET(uint16_t instc);

void op_RTI(uint16_t instc);

void op_ST(uint16_t instc);

void op_STI(uint16_t instc);

void op_STR(uint16_t instc);

void op_TRAP(uint16_t instc);
