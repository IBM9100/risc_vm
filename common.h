#pragma once

/* 标准库 */
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

/* Unix */
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/termios.h>
#include <signal.h>

/* 启动内存地址 */
enum { PC_START = 0x3000 };

extern int running;

uint16_t swap16(uint16_t x);

uint16_t check_key();

void disable_input_buffering();

void restore_input_buffering();
