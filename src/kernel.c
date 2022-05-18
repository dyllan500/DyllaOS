#include <mini_uart.h>
#include <printf.h>

void putc(void *p, char c) {
    if (c == '\n') {
        uart_send('\r');
    }

    uart_send(c);
}


static unsigned int processor = 0; // global variable to sync the processors

void kernel_main(char proc_id)
{
    while (processor != proc_id) {} // wait to execute
    if(proc_id == 0)
    {
        uart_init();
        init_printf(0, putc);
        printf("\nDyllaOS Initializing...\n");
    }
    
    
    printf("Hello World!!!!\n");
    
    processor++; // increment 'processor' to enable the next core to execute
    while (1) {
        uart_send(uart_recv());
    }
}
