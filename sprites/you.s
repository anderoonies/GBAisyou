
@{{BLOCK(you)
    .section .rodata
    .align  2
    .global youTiles       @ 128 unsigned chars
    .hidden youTiles
youTiles:
    
    .word 0x11111100, 0x11111110, 0x11111110, 0x11111111, 0x11100110, 0x11100100, 0x11100100, 0x01100001
    
    .word 0x00111111, 0x01111111, 0x01111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x10010110
    
    .word 0x10100111, 0x10110011, 0x10110011, 0x01111001, 0x11111111, 0x11111110, 0x11111110, 0x11111100
    
    .word 0x10010100, 0x10010100, 0x10000100, 0x11001110, 0x11111111, 0x01111111, 0x01111111, 0x00111111
    
    .section .rodata
    .align  2
    .global youPal     @ 4 unsigned chars
    .hidden youPal
youPal:
    .hword 0x0000,0x30fa

@}}BLOCK(you)