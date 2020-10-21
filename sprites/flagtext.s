
@{{BLOCK(flagtext)
    .section .rodata
    .align  2
    .global flagtextTiles       @ 128 unsigned chars
    .hidden flagtextTiles
flagtextTiles:
    
    .word 0x00000000, 0x01111100, 0x01111100, 0x00000110, 0x00111110, 0x00000110, 0x00000110, 0x00000110
    
    .word 0x00000000, 0x00001100, 0x00001100, 0x00001100, 0x00001110, 0x00000110, 0x01111110, 0x01111110
    
    .word 0x00000000, 0x00110000, 0x01111000, 0x01011100, 0x11001100, 0x11111110, 0x11000110, 0x11000110
    
    .word 0x00000000, 0x00111100, 0x01111110, 0x00000110, 0x00110010, 0x01110110, 0x01100110, 0x00111100
    
    .section .rodata
    .align  2
    .global flagtextPal     @ 4 unsigned chars
    .hidden flagtextPal
flagtextPal:
    .hword 0x0000,0x437c

@}}BLOCK(flagtext)