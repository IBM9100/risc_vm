#pragma once
#include "common.h"

/* 中断向量 */
enum {
    TRAP_GETC   = 0x20,     /* 读入字符 */
    TRAP_OUT    = 0x21,     /* 输出字符 */
    TRAP_PUTS   = 0x22,     /* 输出字符串 */
    TRAP_IN     = 0x23,     /* 读入字符并显示 */
    TRAP_PUTSP  = 0x24,     /* 输出位压缩字符串 */
    TRAP_HALT   = 0x25      /* 终止 */
};

/* 中断门 */
inline void trap_gate(uint16_t trap_vect);
