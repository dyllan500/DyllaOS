#include <mini_uart.h>

static unsigned int processor = 0; // global variable to sync the processors

void kernel_main(char proc_id)
{
    while (processor != proc_id) {} // wait to execute
    
    
    uart_send_string("Hello World!!!\n");
    
    processor++; // increment 'processor' to enable the next core to execute
    while (1) {
        uart_send(uart_recv());
    }
}
