#include <string.h>
#include <stdlib.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void agblog(const char *message)
{
    // https://github.com/mgba-emu/mgba/blob/master/opt/libgba/mgba.c

    volatile uint16_t *reg_debug_enable = (uint16_t*)0x4FFF780;
    (*reg_debug_enable) = 0xC0DE;

    int max_characters_per_line = 256;
    volatile uint16_t *reg_debug_string = (uint16_t*)0x4FFF600;
    volatile uint16_t *reg_debug_flags = (uint16_t*)0x4FFF700;
    int characters_left = strlen(message);

    while(characters_left > 0)
    {
        int characters_to_write = MIN(characters_left, max_characters_per_line);
        memcpy(reg_debug_string, message, characters_to_write);
        (*reg_debug_flags) = 2 | 0x100;
        characters_left -= characters_to_write;
    }
}