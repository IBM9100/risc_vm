#include "common.h"
#include "memory.h"
#include "register.h"
#include "isa.h"

/* 
 *  1. 从 R_PC 读入指令
 *  2. 递增 PC
 *  3. 执行 opcode
 *  4. 跳到 1
 */

int running = 1;

void handle_interrupt(int signal) {
    restore_input_buffering();
    printf("\n");
    exit(-2);
}

int main(int argc, const char* argv[]){

    /* 载入内存镜像 */
    if(argc < 2){
        printf("\033[1;35m请传入内存镜像文件地址. \033[0m");
        printf("\033[1;32meg: riscvm [image-file] ...\n\033[0m");
        exit(2);
    }

    for (int i = 1; i < argc; i++){
        if(!read_image(argv[i])){
            printf("\033[1;31m内存镜像文件加载失败: %s\n\033[0m", argv[i]);
            exit(1);
        }
    }

    /* 初始化 */

    signal(SIGINT, handle_interrupt);
    disable_input_buffering();
    
    /* CPU加电稳定后执行的第一条指令 */
    reg[R_PC] = PC_START;
    
    while(running){
        uint16_t instrc = mem_read(reg[R_PC]++);
        uint16_t op = instrc >> 12;
        
        switch (op)
        {
        case OP_ADD:
            op_ADD(instrc);
            break;
        case OP_AND:
            op_AND(instrc);
            break;
        case OP_BR:
            op_BR(instrc);
            break;
        case OP_JMP:
            op_JR(instrc);
            break;
        case OP_JSR:
            op_JSR(instrc);
            break;
        case OP_LD:
            op_LD(instrc);
            break;
        case OP_LDI:
            op_LDI(instrc);
            break;
        case OP_LDR:
            op_LDR(instrc);
            break;
        case OP_LEA:
            op_LEA(instrc);
            break;
        case OP_NOT:
            op_NOT(instrc);
            break;
        case OP_ST:
            op_ST(instrc);
            break;
        case OP_STI:
            op_STI(instrc);
            break;
        case OP_STR:
            op_STR(instrc);
            break;
        case OP_TRAP:
            op_TRAP(instrc);
            break;
        case OP_RES:
        case OP_RTI:
        default:
            abort();
            break;
        }
    }
    /* 关机 */
    restore_input_buffering();
}
