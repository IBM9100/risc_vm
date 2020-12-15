#include "common.h"
#include "memory.h"
#include "register.h"

/* 
 *  1. 从 R_PC 读入指令
 *  2. 递增 PC
 *  3. 执行 opcode
 *  4. 跳到 1
 */

int running = 1;

int main(int argc, const char* argv[]){
    
    /* CPU加电稳定后执行的第一条指令 */
    reg[R_PC] = PC_START;
    
    while(running){
        uint16_t instrc = mem_read(reg[R_PC]++);
        uint16_t op = instrc >> 12;
    }
}
