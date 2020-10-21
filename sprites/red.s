
@{{BLOCK(red)
    .section .rodata
    .align  2
    .global redTiles       @ 128 unsigned chars
    .hidden redTiles
redTiles:
    
    .word 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    
    .word 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    
    .word 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    
    .word 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
    
    .section .rodata
    .align  2
    .global redPal     @ 4 unsigned chars
    .hidden redPal
redPal:
    .hword 0x001f

@}}BLOCK(red)