#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

#include "core.h"

static void host_sleep(uint8_t ms)
{
    sleep((unsigned int) ms);
}

static void host_log(char const * const text)
{
    printf("%s\n", text);
}

int main(int argc, char const *argv[])
{
    struct core_s core = {0};

    core_init(&core, (struct core_hal_s){
        .log = host_log,
        .sleep = host_sleep
    });
    
    while(true) {
        core_loop(&core);
    }

    return 0;
}
