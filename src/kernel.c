#include <mini_uart.h>
#include <printf.h>
#include <mailbox.h>

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
    
    printf("Clock CORE: %d\n", mailbox_clock_rate(CT_CORE));
    printf("Clock EMMC: %d\n", mailbox_clock_rate(CT_EMMC));
    printf("Clock UART: %d\n", mailbox_clock_rate(CT_UART));
    printf("Clock ARMZ: %d\n", mailbox_clock_rate(CT_ARM));

 
    u32 max_temp = 0;

    mailbox_generic_command(RPI_FIRMWARE_GET_MAX_TEMPERATURE, 0, &max_temp);
    //processor++; // increment 'processor' to enable the next core to execute
    while (1) {
        u32 cur_temp = 0;

        mailbox_generic_command(RPI_FIRMWARE_GET_TEMPERATURE, 0, &cur_temp);

        printf("Cur temp: %dC MAX: %dC\n", cur_temp / 1000, max_temp / 1000);
        //uart_send(uart_recv());
    }
}
