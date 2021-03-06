#include "common.h"
#include "isa.h"
#include "register.h"
#include "memory.h"
#include "trap.h"


/* 有符号扩展, 将low视为补码有符号数 */
uint16_t sign_extend(uint16_t low, uint16_t len){
    if(low >> (len - 1) & 1){
        low |= (0xFFFF << len);
    }
    return low;
}

/* rx: 寄存器号 */
void update_flags(uint16_t rx){
    if(reg[rx] == 0) reg[R_COND] = FL_ZRO;
    else if(reg[rx] >> 15) reg[R_COND] = FL_NEG;
    else reg[R_COND] = FL_POS;
}

/* 指令集实现 */
/* 加法 */
void op_ADD(uint16_t instc){
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

/* 按位与 */
void op_AND(uint16_t instc){
    uint16_t r0 = (instc >> 9) & 0x7;
    uint16_t r1 = (instc >> 6) & 0x7;
    uint16_t imm_flag = (instc >> 5) & 0x1;
    
    if(imm_flag){
        uint16_t imm = instc & 0x1F;
        reg[r0] = reg[r1] & sign_extend(imm, 5);        
    }else{
        uint16_t r2 = instc & 0x7;
        reg[r0] = reg[r1] & reg[r2];
    }

    update_flags(r0);
}

/* 间接内存寻址 */
void op_LDI(uint16_t instc){
    uint16_t r0 = (instc >> 9) & 0x7;
    uint16_t addr_offset = instc & 0x1FF;
    uint16_t addr_mem = reg[R_PC] + sign_extend(addr_offset, 9);
    reg[r0] = mem_read(mem_read(addr_mem));

    update_flags(r0);
}

/* 条件跳转 */
void op_BR(uint16_t instc){
    uint16_t cond_flags = (instc >> 9) & 0x7;

    if(cond_flags & reg[R_COND]){
        reg[R_PC] += sign_extend(instc & 0x1FF, 9);
    }
}

/* jump and RET */
void op_JR(uint16_t instc){
    uint16_t r0 = (instc >> 6) & 0x7;
    reg[R_PC] = reg[r0];
}

/* jump 子例程 */
void op_JSR(uint16_t instc){
    /*  JSR     LABEL
        JSRR    BaseR */
    uint16_t imm_flag = (instc >> 11) & 0x1;
    /* 保护上下文 */
    reg[R_R7] = reg[R_PC];
    if(imm_flag){
        reg[R_PC] += sign_extend(instc & 0x7FF, 11);
    }else{
        uint16_t r0 = (instc >> 6) & 0x7;
        reg[R_PC] = reg[r0];
    }
}

/* Load PC + offset */
void op_LD(uint16_t instc){
    uint16_t r0 = (instc >> 9) & 0x7;
    reg[r0] = mem_read(reg[R_PC] + sign_extend(instc & 0x1FF, 9));

    update_flags(r0);
}

/* Load Base + offset */
void op_LDR(uint16_t instc){
    uint16_t r0 = (instc >> 9) & 0x7;
    uint16_t r1 = (instc >> 6) & 0x7;
    uint16_t offset = instc & 0x3F;
    reg[r0] = mem_read(reg[r1] + sign_extend(offset, 6));

    update_flags(r0);
}

/* Load effective address */
void op_LEA(uint16_t instc){
    uint16_t r0 = (instc >> 9) & 0x7;
    reg[r0] = reg[R_PC] + sign_extend(instc & 0x1FF, 9);

    update_flags(r0);
}

/* 按位 NOT */
void op_NOT(uint16_t instc){
    uint16_t r0 = (instc >> 9) & 0x7;
    uint16_t r1 = (instc >> 6) & 0x7;
    reg[r0] = ~reg[r1];

    update_flags(r0);
}

/* 用户态返回 */
void op_RET(uint16_t instc){
    op_BR(instc);
}

/* 中断返回 类似x86/IRET */
void op_RTI(uint16_t instc){
    //TODO: Return from interrupt;
    abort();
}

/* Store 直接内存写入 */
void op_ST(uint16_t instc){
    uint16_t pc_offset = sign_extend(instc & 0x1FF, 9);
    uint16_t r0 = (instc >> 9) & 0x7;
    mem_write(reg[R_PC] + pc_offset, reg[r0]);
}

/* Store Indirect 间接内存写入 */
void op_STI(uint16_t instc){
    uint16_t pc_offset = sign_extend(instc & 0x1FF, 9);
    uint16_t r0 = (instc >> 9) & 0x7;
    mem_write(mem_read(reg[R_PC] + pc_offset), reg[r0]);
}

/* Store Base + offset 变基址内存写入 */
void op_STR(uint16_t instc){
    uint16_t r0 = (instc >> 9) & 0x7;
    uint16_t r1 = (instc >> 6) & 0x7;
    uint16_t r_offset = sign_extend(instc & 0x3F, 6);
    mem_write(reg[r1] + r_offset, reg[r0]);
}

/* 中断陷入 */
void op_TRAP(uint16_t instc){
    trap_gate(instc & 0xFF);
}
