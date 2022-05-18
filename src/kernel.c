#include <mini_uart.h>
#include <printf.h>
#include <mailbox.h>
#include <video.h>

void putc(void *p, char c) {
    if (c == '\n') {
        uart_send('\r');
    }

    uart_send(c);
}


static u32 processor = 0; // global variable to sync the processors

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
    
    printf("Resolution 1920x1080\n");
    video_set_resolution(1920, 1080, 32);
    
    u32 colors[5] = {0x5500BBFF, 0x0000BBFF, 0x0055BBFF, 0xAA0000FF, 0x9922BBFF};
    int color = 0;
    
    //processor++; // increment 'processor' to enable the next core to execute
    while (TRUE) {
        video_draw_rect(1920, 1080, colors[color]);
        color++;
        if(color >= 5)
        {
            color = 0;
        }
    }
}
