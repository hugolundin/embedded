#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "pico.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"

queue_t queue;

bool repeating_timer_callback(struct repeating_timer *t)
{
    char c = 'c';
    queue_try_add(&queue, (void *) &c);

    return true;
}

int main(int argc, char const *argv[])
{
    stdio_init_all();
    queue_init(&queue, sizeof(char), 10);

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    char c;
    uint8_t ret;
    struct repeating_timer timer;
    add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);

    for(;;) {
        queue_remove_blocking(&queue, &c);
        printf("%c\n", c);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(250);
    }
}
