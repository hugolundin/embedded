#pragma once

#include <stdint.h>

struct core_hal_s {
    void (*log)(char const * const text);
    void (*sleep)(uint8_t ms);
};

struct core_s {
    struct core_hal_s hal;
};

int core_init(
    struct core_s * core,
    struct core_hal_s hal
);

void core_loop(struct core_s * core);
