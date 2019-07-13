#pragma once

/* Register */
enum{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,       //8个通用寄存器
    R_PC,       //两个专用寄存器
    R_COND,     //EFLAGS
    R_COUNT
};
