#include "common.h"
#include "isa.h"
#include "register.h"

/* 有符号扩展, 将low视为补码有符号数 */
inline uint16_t sign_extend(uint16_t low, uint16_t len){
    if(low >> (len - 1) & 1){
        low |= (0xFFFF << len);
    }
    return low;
}

/* rx: 寄存器号 */
inline void update_flags(uint16_t rx){
    if(reg[rx] == 0) reg[R_COND] = FL_ZRO;
    else if(reg[rx] >> 15) reg[R_COND] = FL_NEG;
    else reg[R_COND] = FL_POS;
}

/* 指令集实现 */
inline void op_add(uint16_t instc){
    /* 0x7: 通用寄存器掩码 */
    /* destination register */
    uint16_t r0 = (instc >> 9) & 0x7;
    /* SR1 */
    uint16_t r1 = (instc >> 6) & 0x7;
    /* 0/SR2 1/imm5 */
    uint16_t imm_flag = (instc >> 5) & 0x1;

    if(imm_flag){
        reg[r0] = reg[r1] + (sign_extend(instc & 0x1F, 5));
    }else{
        uint16_t r2 = instc & 0x7;
        reg[r0] = reg[r1] + reg[r2];
    }

    update_flags(r0);
}
