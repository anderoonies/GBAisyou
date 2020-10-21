
@{{BLOCK(is)
    .section .rodata
    .align  2
    .global isTiles       @ 128 unsigned chars
    .hidden isTiles
isTiles:
    
    .word 0x00000000, 0x00000000, 0x00110000, 0x00110000, 0x00110000, 0x00110000, 0x00011000, 0x00011000
    
    .word 0x00000000, 0x00000000, 0x00000000, 0x00111100, 0x01100110, 0x01100011, 0x00000011, 0x00000110
    
    .word 0x00011000, 0x00011000, 0x10011000, 0x10001100, 0x10001100, 0x00001100, 0x00000000, 0x00000000
    
    .word 0x00001100, 0x00011000, 0x00110000, 0x00110001, 0x00011001, 0x00001111, 0x00000000, 0x00000000
    
    .section .rodata
    .align  2
    .global isPal     @ 4 unsigned chars
    .hidden isPal
isPal:
    .hword 0x0000,0x7fff

@}}BLOCK(is)