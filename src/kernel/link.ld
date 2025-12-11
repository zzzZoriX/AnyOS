ENTRY(kernel_main)
SECTIONS {
    . = 0x1000;

    .text : {
        *(.text*)
    } :text

    .rodata : {
        *(.rodata*)
    } :rodata

    .data : {
        *(.data*)
    } :data

    .bss : {
        *(.bss*)
        *(COMMON)
    } :bss

    . = ALIGN(4096);
}

PHDRS {
    text PT_LOAD FLAGS(5);
    rodata PT_LOAD FLAGS(4); 
    data PT_LOAD FLAGS(6);
    bss PT_LOAD FLAGS(6);
}