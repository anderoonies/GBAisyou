
@{{BLOCK(wall)
    .section .rodata
    .align  2
    .global wallTiles       @ 128 unsigned chars
    .hidden wallTiles
wallTiles:
    
    .word 0x00000000, 0x11111110, 0x11111101, 0x00000001, 0x11111110, 0x00000000, 0x11001111, 0x11001111
    
    .word 0x00000000, 0x01111111, 0x10111111, 0x10000000, 0x01111111, 0x00000000, 0x01011100, 0x01111101
    
    .word 0x11100111, 0x00000000, 0x10111110, 0x10111110, 0x10001000, 0x00110001, 0x01110011, 0x01110111
    
    .word 0x01111101, 0x00000000, 0x11111011, 0x11111011, 0x11000011, 0x00011000, 0x10011111, 0x10011111
    
    .section .rodata
    .align  2
    .global wallPal     @ 4 unsigned chars
    .hidden wallPal
wallPal:
    .hword 0x0000,0x35ad

@}}BLOCK(wall)