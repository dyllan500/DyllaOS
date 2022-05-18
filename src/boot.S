#include "mm.h"

.section ".text.boot"

.globl _start
_start:
    mrs    x0, mpidr_el1
    and    x0, x0,#0xFF     // get processor id
    cbz    x0, master
    b      init_stack

proc_hang: 
    b      proc_hang

// only the primary cpu needs to initialize the memory
master:
    adr    x0, bss_begin
    adr    x1, bss_end
    sub    x1, x1, x0
    bl     memzero

init_stack:
    mrs    x0, mpidr_el1
    and    x0, x0,#0xFF     // get processor id again
    mov    x1, x0
    mov    x2, #0x1000
    mul    x1, x1, x2
    add    x1, x1, #LOW_MEMORY
    mov    sp, x1
    bl    kernel_main
