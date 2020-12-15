#include "common.h"

/* 小端到大端 */
uint16_t swap16(uint16_t x) {
    return (x << 8) | (x >> 8);
}

/* 平台相关 按键检测 */
uint16_t check_key() {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(1, &readfds, NULL, NULL, &timeout) != 0;
}
