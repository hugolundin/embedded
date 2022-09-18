#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "pico.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main(int argc, char const *argv[])
{
    stdio_init_all();
    cyw43_arch_init();

    printf("hello world!\n");

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }
}
