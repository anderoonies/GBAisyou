
@{{BLOCK(babatext)
    .section .rodata
    .align  2
    .global babatextTiles       @ 128 unsigned chars
    .hidden babatextTiles
babatextTiles:
    
    .word 0x00000000, 0x00111100, 0x01101100, 0x01101100, 0x00111100, 0x01100110, 0x01100110, 0x00111110
    
    .word 0x00000000, 0x00111000, 0x00101100, 0x01100100, 0x01100110, 0x01111110, 0x01100110, 0x01000011
    
    .word 0x00000000, 0x00111100, 0x01101100, 0x01101100, 0x00111100, 0x01100110, 0x01100110, 0x00111110
    
    .word 0x00000000, 0x00111000, 0x00101100, 0x01100100, 0x01100110, 0x01111110, 0x01100110, 0x01000011
    
    .section .rodata
    .align  2
    .global babatextPal     @ 4 unsigned chars
    .hidden babatextPal
babatextPal:
    .hword 0x0000,0x30fa

@}}BLOCK(babatext)