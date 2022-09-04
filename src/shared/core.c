#include "core.h"

int core_init(struct core_s * core, struct core_hal_s hal)
{
    core->hal = hal;
    return 0;
}

void core_loop(struct core_s * core)
{
    core->hal.log("hello world!");
    core->hal.sleep(1);
}
