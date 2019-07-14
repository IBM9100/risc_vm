#pragma once;
#include "common.h"

/* Memory 十六位地址空间 */
uint16_t memory[UINT16_MAX];

uint16_t mem_read(uint16_t address);
