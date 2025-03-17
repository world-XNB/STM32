#ifndef ASYNC_UART_H
#define ASYNC_UART_H

void async_uart_init();

int async_uart_sendData(const char* logName, const char* data);

// static void async_uart_tx_task(void *arg);

// static void async_uart_rx_task(void *arg);

void uart_app_main();

#endif // ASYNC_UART_H