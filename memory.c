#include "memory.h"

/* 镜像文件映射到内存的全地址空间 */
void read_image_file(FILE *file){
    /* Original Entry Point */
    uint16_t oep;
    fread(&oep, sizeof(oep), 1, file);
    swap16(oep);

    uint16_t max_size = UINT16_MAX - sizeof(oep);
    uint16_t* mem_start = memory + oep;
    size_t len = fread(mem_start, sizeof(uint16_t), max_size, file);
    while(len--){
        *mem_start = swap16(*mem_start);
        ++mem_start;
    }
}

int read_image(const char* image_path){
    FILE *p = fopen(image_path, "rb");
    if(!p) return 0;
    read_image_file(p);
    fclose(p);
    return 1;
}

void mem_write(uint16_t address, uint16_t content){
    memory[address] = content;
}

uint16_t mem_read(uint16_t address){
    if(address == MR_KBSR){
        if(check_key()){
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getchar();
        }else{
            memory[MR_KBSR] = 0;
        }
    }
    return memory[address];
}
