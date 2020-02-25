#include "Map.h"

Plant::Plant(int hp, int type, string name) {
	this->hp = hp;
	this->type = type;
	this->name = name;
}

void Plant::set_xy(int x, int y) {
	this->x = x;
	this->y = y;
}

int Plant::get_hp() {
	return hp;
}

void Plant::under_attack(int damage) {
	hp -= damage;
}

void Plant::display() {
	set_cursor_position(x, y);
	if (type == SUNFLOWER)
		set_text_color(FOREGROUND_RED | FOREGROUND_GREEN);
	else if (type == PEASHOOTER || type == DOUBLE_PEASHOOTER)
		set_text_color(FOREGROUND_GREEN);
	cout << name;
	set_text_color(WHITE);
}

void Plant::clear() {
	set_cursor_position(x, y);
	for (int i = 0; i < CELL_COLUMN; i++)
		cout << " ";
}

Sunflower::Sunflower() :Plant(200, SUNFLOWER, "向日葵") {

}

void Sunflower::function(int step, Player* player, Map *map) {
	if ((step - birth_step) % SUNFLOWER_STEP) {
		return;
	}
	player->sunshine_change(50);
	player->display_sunshine();
}

Peabullet::Peabullet(int x, int y) {
	this->x = x;
	this->y = y;
}

void Peabullet::display() {
	set_cursor_position(x, y);
	set_text_color(FOREGROUND_GREEN);
	cout << "●";
	set_text_color(WHITE);
}

void Peabullet::move(int step, Map *map) {
	if (step % BULLET_STEP) 
		return;
	clear();
	x++;
	while (x % (CELL_COLUMN + 1) == 0 || (x + 1) % (CELL_COLUMN + 1) == 0)
		x++;
	int cell_x = cellx(x);
	int cell_y = celly(y);
	if (cell_x >= MAP_COLUMN || cell_y >= MAP_ROW)
		return;
	if (map->cell[cell_y][cell_x].plant != NULL) {
		y = cell_y * (CELL_ROW + 1) + 1;
	}
	else y = cell_y * (CELL_ROW + 1) + 1;
}

void Peabullet::clear() {
	set_cursor_position(x, y);
	cout << "  ";
}

bool Peabullet::whether_hit(Map *map, Player *player) {
	int cell_x = cellx(x);
	int cell_y = celly(y);
	for (int i = 0; i < CELL_ROW; i++) {
		Zombie* zombie = map->cell[cell_y][cell_x].zombie[i];
		if (zombie != NULL) {
			zombie->under_attack(100);
			if (zombie->get_hp() <= 0) {
				zombie->clear();
				map->cell[cell_y][cell_x].zombie[i] = NULL;
				delete zombie;
				player->score_increase(100);
				player->display_score();
			}
			return 1;
		}
	}
	return 0;
}

bool Peabullet::outrange() {
	if (cellx(x) >= MAP_COLUMN) {
		return 1;
	}
	else return 0;
}

Peashooter::Peashooter() :Plant(200, PEASHOOTER, "豌豆射手") {
	for (int i = 0; i < MAX_BULLET; i++) {
		bullet[i] = NULL;
	}
}

void Peashooter::generate_bullet() {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullet[i] == NULL) {
			bullet[i] = new Peabullet(x + 9, y);
			break;
		}
	}
}

void Peashooter::function(int step, Player* player, Map *map) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullet[i] != NULL) {
			bullet[i]->move(step, map);
			if (bullet[i]->outrange()||bullet[i]->whether_hit(map, player)) {
				bullet[i]->clear();
				delete bullet[i];
				bullet[i] = NULL;
			}
			else
				bullet[i]->display();
		}
	}
	if (step % PEASHOOTER_STEP) {
		return;
	}
	generate_bullet();	
}

Double_Peashooter::Double_Peashooter() {
	Peashooter();
	type = DOUBLE_PEASHOOTER;
	name = "双发豌豆";
}

void Double_Peashooter::function(int step, Player* player, Map* map) {
	for (int i = 0; i < MAX_BULLET; i++) {
		if (bullet[i] != NULL) {
			bullet[i]->move(step, map);
			if (bullet[i]->outrange() || bullet[i]->whether_hit(map, player)) {
				bullet[i]->clear();
				delete bullet[i];
				bullet[i] = NULL;
			}
			else
				bullet[i]->display();
		}
	}
	if (step % PEASHOOTER_STEP == 0 || (step - 3) % PEASHOOTER_STEP == 0) {
		generate_bullet();
	}

}