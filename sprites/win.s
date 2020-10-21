
@{{BLOCK(win)
    .section .rodata
    .align  2
    .global winTiles       @ 128 unsigned chars
    .hidden winTiles
winTiles:
    
    .word 0x11111100, 0x11111110, 0x11111110, 0x11111111, 0x11111111, 0x10011100, 0x10011100, 0x10010100
    
    .word 0x00111111, 0x01111111, 0x01111111, 0x11111111, 0x11111111, 0x11111111, 0x10110110, 0x10100100
    
    .word 0x10000000, 0x11000001, 0x11101011, 0x11111111, 0x11111111, 0x11111110, 0x11111110, 0x11111100
    
    .word 0x10000100, 0x10010100, 0x10010100, 0x11111111, 0x11111111, 0x01111111, 0x01111111, 0x00111111
    
    .section .rodata
    .align  2
    .global winPal     @ 4 unsigned chars
    .hidden winPal
winPal:
    .hword 0x0000,0x437c

@}}BLOCK(win)