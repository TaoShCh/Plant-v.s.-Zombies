#include "Map.h"

Zombie::Zombie(int hp, int step, int attack, int type, string name) {
	this->hp = hp;
	this->move_interval = step;
	this->attack = attack;
	this->name = name;
	this->type = type;
}

void Zombie::set_xy(int x, int y) {
	this->x = x;
	this->y = y;
}

int Zombie::get_hp() {
	return hp;
}

void Zombie::display() {
	set_cursor_position(x, y);
	cout << name;
}

void Zombie::under_attack(int damage) {
	hp -= damage;
	set_text_color(FOREGROUND_RED);
	display();
	set_text_color(WHITE);
}

void Zombie::clear() {
	set_cursor_position(x, y);
	for (int i = 0; i < name.length(); i++) {
		cout << " ";
	}
}

//return 1 when the zombie eat your brain
int Zombie::move(int step, Map *map) {
	if (step % move_interval)
		return 0;
	int cell_x = cellx(x), cell_y = celly(y);
	if (cell_x == 0)
		return 1;
	Cell* next_cell = &map->cell[cell_y][cell_x - 1];
	Cell* cell = &map->cell[cell_y][cell_x];
	if (next_cell->plant == NULL) {
		for (int i = 0; i < CELL_ROW; i++) {
			if (next_cell->zombie[i] == NULL) {
				next_cell->zombie[i] = this;
				for (int j = 0; j < CELL_ROW; j++) {
					if (cell->zombie[j] == this) {
						cell->zombie[j] = NULL;
						break;
					}
				}
				clear();
				set_xy(x - CELL_COLUMN - 1, cell_y * (CELL_ROW + 1) + i + 1);
				break;
			}
		}
	}
	else {
		Plant* plant = next_cell->plant;
		plant->under_attack(attack);
		if (plant->get_hp() <= 0) {
			next_cell->plant = NULL;
			plant->clear();
			delete plant;
		}
	}
	return 0;
}

Normal_zombie::Normal_zombie() :Zombie(500, 80, 100, NORMAL_ZOMBIE, "½©Ê¬") {

}

Roadblock_zombie::Roadblock_zombie() : Zombie(1000, 80, 100, ROADBLOCK_ZOMBIE, "Â·ÕÏ½©Ê¬") {

}