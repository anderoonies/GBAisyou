
@{{BLOCK(walltext)
    .section .rodata
    .align  2
    .global walltextTiles       @ 128 unsigned chars
    .hidden walltextTiles
walltextTiles:
    
    .word 0x00000000, 0x11000110, 0x11000110, 0x11000110, 0x11100110, 0x11110110, 0x11111100, 0x01101100
    
    .word 0x00000000, 0x01110000, 0x11011000, 0x11001000, 0x11111100, 0x11101100, 0x11000110, 0x11000110
    
    .word 0x00000000, 0x00001100, 0x00001100, 0x00001100, 0x00000110, 0x00000110, 0x01111110, 0x01111110
    
    .word 0x00000000, 0x00001100, 0x00001100, 0x00001100, 0x00000110, 0x00000110, 0x01111110, 0x01111110
    
    .section .rodata
    .align  2
    .global walltextPal     @ 4 unsigned chars
    .hidden walltextPal
walltextPal:
    .hword 0x0000,0x35ad

@}}BLOCK(walltext)