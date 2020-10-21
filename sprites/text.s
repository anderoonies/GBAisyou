
@{{BLOCK(text)
    .section .rodata
    .align  2
    .global textTiles       @ 128 unsigned chars
    .hidden textTiles
textTiles:
    
    .word 0x01111110, 0x00010000, 0x00010000, 0x00010000, 0x00001000, 0x00001000, 0x00001000, 0x00000000
    
    .word 0x00111110, 0x00000010, 0x00000010, 0x00001110, 0x00000001, 0x00000001, 0x00011111, 0x00000000
    
    .word 0x01000100, 0x01000100, 0x00100100, 0x00011000, 0x00011000, 0x00100100, 0x00100010, 0x00100010
    
    .word 0x00111111, 0x00001000, 0x00001000, 0x00001000, 0x00001000, 0x00000100, 0x00000100, 0x00000100
    
    .section .rodata
    .align  2
    .global textPal     @ 4 unsigned chars
    .hidden textPal
textPal:
    .hword 0x0000,0x30da

@}}BLOCK(text)