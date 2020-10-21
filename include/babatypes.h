#ifndef BABA_TYPES
#define BABA_TYPES

typedef struct GameTile {
    // lookup for the tilemap
    uint8_t tileindex;
    char nice_name[10];
    // part of speech, for chaining sentences.
    // a valid sentence is noun -> verb -> prop (later AND or NOT)
    enum{none, noun, verb, prop} part;
    // what GameTile "names" this one.
    // i.e. the tile with the sheep is named by the tile 
    // with the word "baba" on it, and any text tile
    // is named by a tile with the word "text" on it
    uint8_t name;
    // tiles and palette
    const unsigned short *palette;
    const char *tiles;
} GameTile;

typedef struct coord {
    uint8_t row;
    uint8_t col;
} coord;

typedef struct move {
    struct coord start;
    struct coord end;
} move;

typedef int rule[3];

typedef struct rules {
    uint8_t n_rules;
    // right now there are a max of 10 rules,
    // because i am not sure how to make this dynamic
    rule rules[10];
} rules;

#endif // BABA_TYPES
