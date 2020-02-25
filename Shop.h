#pragma once
#include "common.h"
class Map;
class Player;
class Goods {
	friend class Shop;
private:
	int price;
	string name;
	int type;
	int y;
public:
	Goods();
	void set_attr(int p, string n, int i);
	void display();
};

class Shop
{
private:
	Goods* goods;
	int state;
	int r, c;//chosen cell
	int chosen;//chosen goods
	void display_red_cell(Map *map);
public:
	Shop();
	void display_goods();
	void get_key(Map *m, Player *player, int step);
};

