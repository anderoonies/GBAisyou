#include <stdio.h>
#include <stdlib.h>
#include <tonc.h>
#include <string.h>
#include "levels.h"
#include "babatypes.h"
#include "sprites.h"

OBJ_ATTR obj_buffer[128];

#define X_BOUND(X) MIN(MAX(0,X),15)
#define Y_BOUND(X) MIN(MAX(0,X),10)

#define BASE_LAYER 0
#define PASS_LAYER 1

// yoinked from brogue
// additional iteration direction for movement
const short dirs[8][3] = {{-1,0, 1}, {0,1,-1}, {1,0,-1}, {0,-1,1}};

typedef int cell[2];

GameTile gt_empty;
GameTile gt_baba;
GameTile gt_word_baba;
GameTile gt_word_is;
GameTile gt_word_you;
GameTile gt_text;
GameTile gt_wall;
GameTile gt_walltext;
GameTile gt_stop;
GameTile gt_flag;
GameTile gt_flagtext;
GameTile gt_win;
GameTile gt_push;
GameTile gt_red;

GameTile tiles[14];

void tile_init() {
    char debugstr[30];
    gt_empty = (struct GameTile){0, "empty", none, -1, babaPal, babaTiles};
    gt_baba = (struct GameTile){1, "baba", none, 2,babaPal, babaTiles};
    gt_word_baba = (struct GameTile){2, "\"baba\"", noun, 5,babatextPal, babatextTiles};
    gt_word_is = (struct GameTile){3, "\"is\"", verb, 5,isPal, isTiles};
    gt_word_you = (struct GameTile){4, "\"you\"", prop, 5,youPal, youTiles};
    gt_text = (struct GameTile){5, "text", noun, -1,textPal, textTiles};
    gt_wall = (struct GameTile){6, "wall", noun, 8,wallPal, wallTiles};
    gt_stop = (struct GameTile){7, "\"stop\"", prop, 5,stopPal, stopTiles};
    gt_walltext = (struct GameTile){8, "\"wall\"", noun, 5,walltextPal, walltextTiles};
    gt_flag = (struct GameTile){9, "flag", noun, 10,flagPal, flagTiles};
    gt_flagtext = (struct GameTile){10, "\"flag\"", noun, 5,flagtextPal, flagtextTiles};
    gt_win = (struct GameTile){11, "\"win\"", prop, 5,winPal, winTiles};
    gt_red = (struct GameTile){14, "\"red\"", prop, 5,redPal, redTiles};
    // TODO
    gt_push = (struct GameTile){12, "\"push\"", prop, 5,winPal, winTiles};


    tiles[0] = gt_empty;
    tiles[1] = gt_baba;
    tiles[2] = gt_word_baba;
    tiles[3] = gt_word_is;
    tiles[4] = gt_word_you;
    tiles[5] = gt_text;
    tiles[6] = gt_wall;
    tiles[7] = gt_stop;
    tiles[8] = gt_walltext;
    tiles[9] = gt_flag;
    tiles[10] = gt_flagtext;
    tiles[11] = gt_win;
    tiles[12] = gt_push;
    tiles[13] = gt_red;
    
    int dt = 4;
    int dp = 16;
    int offset = 0;
    int tile;
    size_t n_tiles = sizeof(tiles)/sizeof(GameTile);
    for (tile = 0; tile < n_tiles; tile++) {
        sprintf(debugstr, "%d", sizeof(tiles[tile].tiles));
        agblog(debugstr);
        memcpy32(&tile_mem[4][offset*dt], tiles[tile].tiles, 32);
        memcpy16(pal_obj_mem + (offset-1)*dp, tiles[tile].palette, 4);
        offset++;
    }
}

// TODO turn this into the "name" thing i added to GameTile
uint8_t tile_for_noun[] = {
  0, 0, 1,
  // etc...
};

bool rule_check(int subject, int prop, struct rules* rules) {
    char debugstr[25];
    for (int i = 0; i < rules->n_rules; i++) {
        // sprintf(debugstr, "%d %d %d", rules->rules[i][0], rules->rules[i][1], rules->rules[i][2]);
        // agblog(debugstr);
        if (
            rules->rules[i][0] == tiles[subject].name &&
            rules->rules[i][1] == gt_word_is.tileindex &&
            rules->rules[i][2] == prop
        ) {
            return true;
        }
    }
    return false;
}

struct rules* collect_rules(struct rules* new_rules) {
    int cell;
    int rule_n = 0;
    // ALWAYS text is pushable!
    memcpy(new_rules->rules[rule_n++], (rule){5, 3, 12}, sizeof(rule));
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            for (int layer = 0; layer < 2; layer++) {
                cell = level[row][col][layer];
                if (
                    tiles[cell].part == noun &&
                    tiles[level[Y_BOUND(row+1)][X_BOUND(col)][layer]].part == verb &&
                    tiles[level[Y_BOUND(row+2)][X_BOUND(col)][layer]].part == prop
                ) {
                    rule new_rule = {
                        level[row][col][layer],
                        level[Y_BOUND(row+1)][X_BOUND(col)][layer],
                        level[Y_BOUND(row+2)][X_BOUND(col)][layer]
                    };
                    memcpy(new_rules->rules[rule_n++], new_rule, sizeof(rule));
                }
                if (
                    tiles[cell].part == noun &&
                    tiles[level[Y_BOUND(row)][X_BOUND(col+1)][layer]].part == verb &&
                    tiles[level[Y_BOUND(row)][X_BOUND(col+2)][layer]].part == prop
                ) {
                    rule new_rule = {
                        level[row][col][layer],
                        level[Y_BOUND(row)][X_BOUND(col+1)][layer],
                        level[Y_BOUND(row)][X_BOUND(col+2)][layer]
                    };
                    memcpy(new_rules->rules[rule_n++], new_rule, sizeof(rule));
                }
            }
        }
    }
    new_rules->n_rules = rule_n;
    print_rules(new_rules);
    return new_rules;
}

bool impassible(int tileindex, struct rules* rules) {
    return rule_check(tileindex, gt_stop.tileindex, rules) || rule_check(tileindex, gt_push.tileindex, rules);
}

bool pushable(int tileindex, struct rules* rules) {
    if (tiles[tileindex].name == 5) {
        return true;
    }
    return rule_check(tileindex, gt_push.tileindex, rules);
}

struct coord scan_for_empty(int d, int r, int c, struct rules* rules, int level_copy[10][15][2]) {
    int cr = r + dirs[d][0];
    int cc = c + dirs[d][1];
    bool tileempty;
    coord next_empty = {r, c};
    while (cr >= 0 && cr < 10 && cc >= 0 && cc < 15) {
        tileempty = true;
        for (int li = 0; li < 2; li++) {
            if (
                level_copy[cr][cc][li] > 0 &&
                impassible(level_copy[cr][cc][li], rules)
            ) {
                tileempty = false;
            }
            if (rule_check(level_copy[cr][cc][li], gt_stop.tileindex, rules)) {
                return next_empty;
            }
        }
        if (tileempty) {
            next_empty.row = cr;
            next_empty.col = cc;
            return next_empty;
        }
        cr += dirs[d][0];
        cc += dirs[d][1];
    }

    return next_empty;
}

void print_rules(rules *rules) {
    agblog("rules:");
    char debugstr[30];
    for(int i = 0; i < rules->n_rules; i++) {
        sprintf(
            debugstr,
            "%s,%s,%s",
            tiles[rules->rules[i][0]].nice_name,
            tiles[rules->rules[i][1]].nice_name,
            tiles[rules->rules[i][2]].nice_name
        );
        agblog(debugstr);
    }
}

// returns the # yous
int collect_yous(coord *yous, rules *rules) {
    char debugstr[25];
    int n_yous = 0;
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            if (
                level[row][col][BASE_LAYER] > 0 &&
                rule_check(level[row][col][BASE_LAYER], gt_word_you.tileindex, rules)
            ) {
                sprintf(debugstr, "%d,%d is you", row, col);
                agblog(debugstr);
                yous[n_yous++] = (struct coord){row, col};
            }
            if (
                level[row][col][PASS_LAYER] > 0 &&
                rule_check(level[row][col][PASS_LAYER], gt_word_you.tileindex, rules)
            ) {
                // flip it!!!
                int you = level[row][col][PASS_LAYER];
                memcpy(&level[row][col][PASS_LAYER], &level[row][col][BASE_LAYER], sizeof(int));
                level[row][col][BASE_LAYER] = you;
                sprintf(debugstr, "%d,%d is you", row, col);
                agblog(debugstr);
                agblog("flipped");
                yous[n_yous++] = (struct coord){row, col};
            }
        }
    }
    return n_yous;
}

void update(int d, struct rules* new_rules) {
    agblog("----");
    int level_copy[10][15][2];
    memcpy(level_copy, level, sizeof(level));
    struct coord copy_destination;
    int cr, cc;
    char debugstr[25];
    new_rules = collect_rules(new_rules);
    coord copysource;
    struct coord *yous = malloc(sizeof(coord) * 150);
    int n_yous = collect_yous(yous, new_rules);
    u8 row, col;
    int i = 0;
    // these are weird bc we need to start from the bottom so we
    // make room for the previous Yous to move
    if (d == 1 || d == 2) {
        i = n_yous - 1;
    }

    sprintf(debugstr, "there are %d yous", n_yous);
    agblog(debugstr);
    for (; i < n_yous && i >= 0; i+=dirs[d][2]) {
        row = yous[i].row;
        col = yous[i].col;
        copy_destination = scan_for_empty(d, row, col, new_rules, level_copy);
        cr = copy_destination.row;
        cc = copy_destination.col;
        yous[i].row = cr;
        yous[i].col = cc;
        for (
            ;
            cr != row || cc != col;
            cr -= dirs[d][0],
            cc -= dirs[d][1]
        ) {
            copysource.row = cr - dirs[d][0];
            copysource.col = cc - dirs[d][1];
            level_copy[Y_BOUND(cr)][X_BOUND(cc)][PASS_LAYER] = \
                level_copy[Y_BOUND(cr)][X_BOUND(cc)][BASE_LAYER];
            level_copy[Y_BOUND(cr)][X_BOUND(cc)][BASE_LAYER] = \
                level[Y_BOUND(copysource.row)][X_BOUND(copysource.col)][BASE_LAYER];
            level_copy[Y_BOUND(copysource.row)][X_BOUND(copysource.col)][BASE_LAYER] = \
                level[Y_BOUND(copysource.row)][X_BOUND(copysource.col)][PASS_LAYER];
            level_copy[Y_BOUND(copysource.row)][X_BOUND(copysource.col)][PASS_LAYER] = \
                0;
        }
    }
    memcpy(level, level_copy, sizeof(level));
    check_win(n_yous, yous, new_rules);
    free(yous);
}

void check_win(int n_yous, coord *yous, rules *rules) {
    coord you;
    char debugstr[25];
    for (int i_you = 0; i_you < n_yous; i_you++) {
        you = yous[i_you];
        // sprintf(debugstr, "checking if %d,%d is %d", you.row, you.col, gt_win.tileindex);
        // agblog(debugstr);
        if (
            rule_check(
                level[you.row][you.col][PASS_LAYER],
                gt_win.tileindex,
                rules
            )
        ) {
        tte_printf("#{P:80,40}");
        win_textbox(0, 8, 80-32+1, 232, 80-4, 8);
            tte_write("\n GOOD JOB!\n");
            // tte_printf("#{P:72,64}");
            // tte_printf("Winner!");
        }
    }
}

void win_textbox(uint bgnr, int left, int top, int right, int bottom, uint bldy)
{
    REG_WIN0H= left<<8 | right;
    REG_WIN0V=  top<<8 | bottom;
    REG_WIN0CNT= WIN_ALL | WIN_BLD;
    REG_WINOUTCNT= WIN_ALL;
    
    REG_BLDCNT= (BLD_ALL&~BIT(bgnr)) | BLD_BLACK;
    REG_BLDY= bldy;

    REG_DISPCNT |= DCNT_WIN0;

    tte_set_margins(left, top, right, bottom);
}

void add_tile_to_obj_buffer(int bufferindex, int ti, int x, int y, int pal_shift) {
    GameTile to_draw = tiles[ti];
    OBJ_ATTR *obj = &obj_buffer[bufferindex];
    obj_set_attr(
        obj,
        ATTR0_SQUARE,
        ATTR1_SIZE_16,
        ATTR2_PALBANK(to_draw.tileindex-1) |
        to_draw.tileindex * 4 |
        ATTR2_PRIO(1)
    );
    obj_set_pos(obj, x, y);
}

void draw_level() {
    int buffer_index = 0;
    int tile_index;
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 15; col++) {
            for (int c = 0; c < 2; c++) {
                tile_index = level[row][col][c];
                if (tile_index > 0) {
                    add_tile_to_obj_buffer(
                        buffer_index,
                        tile_index,
                        col * 16,
                        row * 16,
                        0
                    );
                    buffer_index++;
                }
            }
        }
    }
}


//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    // the vblank interrupt must be enabled for VBlankIntrWait() to work
    // since the default dispatcher handles the bios flags no vblank handler
    // is required
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);

    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    oam_init(obj_buffer, 128);
    tile_init();

    tte_init_chr4c_b4_default(0, BG_CBB(2)|BG_SBB(28));
    tte_set_drawg(chr4c_drawg_b4cts_fast);
    tte_init_con();

    struct rules *new_rules = malloc(sizeof(rules));

    tte_printf("#{es;P}");
    int original_level[10][15][2];
    memcpy(original_level, level, sizeof(level));
    while (1) {
        VBlankIntrWait();
        key_poll();
        if (key_hit(KEY_LEFT)) {
            update(3, new_rules);
        } else if (key_hit(KEY_RIGHT)) {
            update(1, new_rules);
        } else if (key_hit(KEY_UP)) {
            update(0, new_rules);
        } else if (key_hit(KEY_DOWN)) {
            update(2, new_rules);
        } else if (key_hit(KEY_A)) {
            memcpy(level, original_level, sizeof(level));
        }
        // oam_init(obj_buffer, 128);
        draw_level();
        oam_copy(oam_mem, obj_buffer, 128);
    }
}
