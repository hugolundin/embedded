#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "pico.h"
#include "pico/stdlib.h"
#include "pico/util/queue.h"

#include "drivers/uart.h"

queue_t uart_queue;
struct embedded_uart_s uart;

static void uart_queue_insert(char c)
{
    queue_try_add(&uart_queue, (void *) &c);
}

static uint8_t uart_queue_get(char *c)
{
    if (queue_try_remove(&uart_queue, c)) {
        return 1;
    }

    return 0;
}

bool repeating_timer_callback(struct repeating_timer *t) {
    embedded_uart_receive(&uart, 'h');
    embedded_uart_receive(&uart, 'e');
    embedded_uart_receive(&uart, 'l');
    embedded_uart_receive(&uart, 'l');
    embedded_uart_receive(&uart, 'o');
    embedded_uart_receive(&uart, '\n');

    return true;
}

int main(int argc, char const *argv[])
{
    stdio_init_all();
    queue_init(&uart_queue, sizeof(char), 10);

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);

    embedded_uart_init(&uart, &(struct embedded_uart_hal_s){
        .queue_insert = uart_queue_insert,
        .queue_get = uart_queue_get
    });

    char c;
    uint8_t ret;
    struct repeating_timer timer;
    add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);

    for(;;) {
        ret = embedded_uart_get(&uart, &c);
        if (ret > 0 && c == 'c') {
            printf("%c", c);
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
            sleep_ms(250);
        }
        
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(250);
    }
}
