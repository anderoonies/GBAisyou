
@{{BLOCK(flag)
    .section .rodata
    .align  2
    .global flagTiles       @ 128 unsigned chars
    .hidden flagTiles
flagTiles:
    
    .word 0x00000000, 0x10110000, 0x10110000, 0x10110000, 0x10110000, 0x10110000, 0x10011000, 0x11011000
    
    .word 0x00000000, 0x00000111, 0x01111111, 0x01111111, 0x01111111, 0x01111111, 0x01111111, 0x01111111
    
    .word 0x00011000, 0x00011000, 0x00011000, 0x00001100, 0x00001100, 0x00001100, 0x00001100, 0x00111110
    
    .word 0x01111100, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    
    .section .rodata
    .align  2
    .global flagPal     @ 4 unsigned chars
    .hidden flagPal
flagPal:
    .hword 0x0000,0x437c

@}}BLOCK(flag)