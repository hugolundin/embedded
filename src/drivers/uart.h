#pragma once

#include <stdint.h>

struct embedded_uart_hal_s {
    void (*queue_insert)(char c);
    uint8_t (*queue_get)(char *c);
};

struct embedded_uart_s {
    struct embedded_uart_hal_s *hal;
};

void embedded_uart_init(
    struct embedded_uart_s *uart,
    struct embedded_uart_hal_s *hal
);

void embedded_uart_receive(struct embedded_uart_s *uart, char c);
uint8_t embedded_uart_get(struct embedded_uart_s *uart, char *c);
