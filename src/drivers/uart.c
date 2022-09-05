#include "uart.h"

void embedded_uart_init(struct embedded_uart_s *uart, struct embedded_uart_hal_s *hal)
{
    uart->hal = hal;
}

void embedded_uart_receive(struct embedded_uart_s *uart, char c)
{
    uart->hal->queue_insert(c);
}

uint8_t embedded_uart_get(struct embedded_uart_s *uart, char *c)
{
    return uart->hal->queue_get(c);
}
