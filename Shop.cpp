#include "Shop.h"
#include "Map.h"

Goods::Goods() {
	name = " ";
}

void Goods::set_attr(int p, string n, int i) {
	price = p;
	name = n;
	type = i;
}

void Goods::display() {
	set_cursor_position(0, y);
	cout << name;
	for (int i = 0; i < PRICE_BEGIN - name.length(); i++)
		cout << " ";
	cout << price;
}

Shop::Shop() {
	state = FREE;
	goods = new Goods[GOODS_NUM];
	chosen = r = c = -1;
	goods[0].set_attr(50, "向日葵", SUNFLOWER);
	goods[0].y = SHOP_START + 1;
	goods[1].set_attr(100, "豌豆射手", PEASHOOTER);
	goods[1].y = SHOP_START + 2;
	goods[2].set_attr(200, "双发豌豆", DOUBLE_PEASHOOTER);
	goods[2].y = SHOP_START + 3;
}

void Shop::display_goods() {
	set_cursor_position(0, MAP_HEIGHT + 5);
	cout << "植物";
	for (int i = 0; i < PRICE_BEGIN - 4; i++)
		cout << " ";
	cout << "价格" << endl;
	for (int i = 0; i < MAP_WIDTH; i++) {
		cout << "-";
	}
	for (int i = 0; i < GOODS_NUM; i++) {
		if (i == chosen) {
			set_text_color(FOREGROUND_RED);
			goods[i].display();
			set_text_color(WHITE);
		}
		else goods[i].display();
	}
}

void Shop::display_red_cell(Map *map) {
	set_text_color(FOREGROUND_RED);
	map->cell[r][c].display_cell_frame();
	set_text_color(WHITE);
}

void Shop::get_key(Map *map, Player *player, int step) {
	int ch = _getch();
	if (ch == 98 && state == FREE) {//b key
		state = SHOPPING;
		chosen = 0;
		display_goods();
	}
	else if (ch == 224) {
		ch = _getch();
		if (ch == 72 && state == SHOPPING) {
			if (chosen > 0) {
				chosen--;
				display_goods();
			}
		}
		else if (ch == 80 && state == SHOPPING) {
			if (chosen < GOODS_NUM - 1) {
				chosen++;
				display_goods();
			}
		}
		else if (ch == 72 && state == PLACING) {
			if (r > 0) {
				map->cell[r][c].display_cell_frame();
				r--;
				display_red_cell(map);
			}
		}
		else if (ch == 80 && state == PLACING) {
			if (r < MAP_ROW - 1) {
				map->cell[r][c].display_cell_frame();
				r++;
				display_red_cell(map);
			}
		}
		else if (ch == 75 && state == PLACING) {
			if (c > 0) {
				map->cell[r][c].display_cell_frame();
				c--;
				display_red_cell(map);
			}
		}
		else if (ch == 77 && state == PLACING) {
			if (c < MAP_COLUMN - 1) {
				map->cell[r][c].display_cell_frame();
				c++;
				display_red_cell(map);
			}
		}
	}
	else if (ch == 13 && state == SHOPPING) {
		state = PLACING;
		r = c = 0;
		display_red_cell(map);
	}
	else if (ch == 13 && state == PLACING) {
		if (player->sunshine >= goods[chosen].price &&
			map->cell[r][c].plant == NULL&&
			map->cell[r][c].zombie[0] == NULL) {
			player->sunshine -= goods[chosen].price;
			player->display_sunshine();
			map->cell[r][c].build_plant(goods[chosen].type, step);
		}
		state = FREE;
		map->cell[r][c].display_cell_frame();
		r = c = chosen = -1;
		display_goods();

	}
	else if (ch == 27 && state == SHOPPING) {
		state = FREE;
		chosen = -1;
		display_goods();
	}
	else if (ch == 27 && state == PLACING) {
		state = FREE;
		map->cell[r][c].display_cell_frame();
		r = c = chosen = -1;
		display_goods();
	}
}