#pragma once
#include "common.h"

/* Register */
enum{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,       /* 8个通用寄存器 */
    R_PC,       /* 两个专用寄存器 */
    R_COND,     /* EFLAGS */
    R_COUNT
};

/* FLAGS */
enum {
    FL_POS = 1 << 0,    /* P */
    FL_ZRO = 1 << 1,    /* Z */
    FL_NEG = 1 << 2,    /* N */
};

uint16_t reg[R_COUNT];
