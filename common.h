#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <conio.h>
using namespace std;

#define MAP_COLUMN 8
#define MAP_ROW 5
#define CELL_COLUMN 10
#define CELL_ROW 3
#define ROAD_WIDTH 20
#define MAP_HEIGHT ((CELL_ROW+1)*MAP_ROW+1)
#define MAP_WIDTH ((CELL_COLUMN+1)*MAP_COLUMN+1)
#define GOODS_FRAME_WIDTH 15
#define SHOP_START (MAP_HEIGHT+6)


#define SUNFLOWER 1
#define PEASHOOTER 2
#define DOUBLE_PEASHOOTER 3
#define GOODS_NUM 3
#define PRICE_BEGIN 15

#define NORMAL_ZOMBIE 1
#define ROADBLOCK_ZOMBIE 2
#define ZOMBIE_TYPE 2

#define SUNFLOWER_STEP 200
#define PEASHOOTER_STEP 30
#define NATURAL_STEP 100
#define BULLET_STEP 1
#define ZOMBIE_APPEAR_STEP 10

#define MAX_BULLET 20

#define SHOPPING 1
#define PLACING 2
#define FREE 3

#define WHITE FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED

void set_cursor_position(int x, int y);
void set_text_color(int attribute);
void game_init();
int cellx(int x);
int celly(int y);
void game_begin();
void game_over();