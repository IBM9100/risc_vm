#include "common.h"
#include "trap.h"
#include "register.h"
#include "memory.h"

/* 中断门与中断服务例程 */
void trap_gate(uint16_t trap_vect){
    switch (trap_vect)
    {
    case TRAP_GETC:
        reg[R_R0] = (uint16_t)getchar();
        break;
    case TRAP_OUT:
        putchar((char)reg[R_R0]);
        fflush(stdout);
        break;
    case TRAP_PUTS:
        {
            uint16_t *p = memory + reg[R_R0];
            while(*p){
                putchar((char)*p);
                ++p;
            }
            fflush(stdout);
        }
        break;
    case TRAP_IN:
        {
            printf("请输入一个字符: ");
            char c = getchar();
            putc(c, stdout);
            reg[R_R0] = (uint16_t)c;
        }
        break;
    case TRAP_PUTSP:
        {
            uint16_t *p = memory + reg[R_R0];
            while(*p){
                char low = (*p) & 0xFF;
                char high = (*p) >> 8;
                putchar(low);
                if(high) putchar(high);
                ++p;
            }
            fflush(stdout);
        }
        break;
    case TRAP_HALT:
        {
            puts("Goodbye~!");
            fflush(stdout);
            running = 0;
        }
        break;
    default:
        abort();
        break;
    }
}
