
@{{BLOCK(baba)
    .section .rodata
    .align  2
    .global babaTiles       @ 128 unsigned chars
    .hidden babaTiles
babaTiles:
    
    .word 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x11111000, 0x11111100, 0x11111100, 0x11111100
    
    .word 0x00000000, 0x00000000, 0x00010001, 0x00001011, 0x00011111, 0x00111111, 0x00101111, 0x00111101
    
    .word 0x11111100, 0x11111100, 0x11111100, 0x11111100, 0x11011000, 0x10010000, 0x00000000, 0x00000000
    
    .word 0x00111111, 0x00011111, 0x00011111, 0x00011111, 0x00011000, 0x00001000, 0x00000000, 0x00000000
    
    .section .rodata
    .align  2
    .global babaPal     @ 4 unsigned chars
    .hidden babaPal
babaPal:
    .hword 0x0000,0x7fff

@}}BLOCK(baba)