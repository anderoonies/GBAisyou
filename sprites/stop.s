
@{{BLOCK(stop)
    .section .rodata
    .align  2
    .global stopTiles       @ 128 unsigned chars
    .hidden stopTiles
stopTiles:
    
    .word 0x11111100, 0x11111110, 0x11111110, 0x11000111, 0x11011011, 0x11111011, 0x11000011, 0x11011111
    
    .word 0x00111111, 0x01111111, 0x01111111, 0x11000000, 0x11110011, 0x11110011, 0x11110011, 0x11111001
    
    .word 0x11100011, 0x11111111, 0x11001111, 0x10010111, 0x10010111, 0x10010110, 0x11001110, 0x11111100
    
    .word 0x11111001, 0x11111111, 0x11100001, 0x11101101, 0x11110001, 0x01111101, 0x01111101, 0x00111111
    
    .section .rodata
    .align  2
    .global stopPal     @ 4 unsigned chars
    .hidden stopPal
stopPal:
    .hword 0x0000,0x0d69

@}}BLOCK(stop)