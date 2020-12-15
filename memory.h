#pragma once
#include "common.h"

/* 内存地址映射 */
enum {
    MR_KBSR = 0xFE00, /* 键盘状态 */
    MR_KBDR = 0xFE02  /* 键盘缓冲区 */
};

/* Memory 十六位地址空间 */
uint16_t memory[UINT16_MAX];

uint16_t mem_read(uint16_t address);

void mem_write(uint16_t address, uint16_t content);

int read_image(const char* image_path);

void read_image_file(FILE *file);
