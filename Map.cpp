#pragma once
#include "Map.h"
Cell::Cell() {
	plant = NULL;
	for (int i = 0; i < CELL_ROW; i++) {
		zombie[i] = NULL;
	}
}

void Cell::set_coordinate(int x, int y) {
	this->x = x;
	this->y = y;
}

void Cell::display_cell_frame() {
	set_cursor_position(x, y);
	for (int i = 0; i < CELL_COLUMN + 2; i++) {
		cout << "#";
	}
	for (int i = 1; i <= CELL_ROW; i++) {
		set_cursor_position(x, y + i);
		cout << "#";
		set_cursor_position(x + CELL_COLUMN + 1, y + i);
		cout << "#";
	}
	set_cursor_position(x, y + CELL_ROW + 1);
	for (int i = 0; i < CELL_COLUMN + 2; i++) {
		cout << "#";
	}
}

void Cell::build_plant(int type, int step) {
	if (plant != NULL) {
		return;
	}
	for (int i = 0; i < CELL_ROW; i++) {
		if (zombie[i] != NULL)
			return;
	}
	switch (type) {
	case SUNFLOWER: {
		plant = (Plant *)new Sunflower();
		break;
	}
	case PEASHOOTER: {
		plant = (Plant*)new Peashooter(); 
		break;
	}
	case DOUBLE_PEASHOOTER: {
		plant = (Plant*) new Double_Peashooter();
	}
	}
	plant->set_xy(x + 3, y + 2);
	plant->birth_step = step;
	display_content();
}

int Cell::place_zombie(int type) {
	for (int i = 0; i < CELL_ROW; i++) {
		if (zombie[i] == NULL) {
			if (type == 0)
				zombie[i] = (Zombie*) new Normal_zombie();
			else if (type == 1)
				zombie[i] = (Zombie*) new Roadblock_zombie();
			zombie[i]->set_xy(this->x + 2, this->y + 1 + i);
			zombie[i]->display();
			return 1;
		}
	}
	return 0;
}

void Cell::display_content() {
	if (plant != NULL) {
		plant->display();
	}
	for (int i = 0; i < CELL_ROW; i++) {
		if (zombie[i] != NULL) {
			zombie[i]->display();
		}
	}
}

Map::Map() {
	cell = new Cell * [MAP_ROW];
	for (int i = 0; i < MAP_ROW; i++) {
		cell[i] = new Cell[MAP_COLUMN + 1];
		for (int j = 0; j < MAP_COLUMN + 1; j++) {
			int x, y;
			x = j * (CELL_COLUMN + 1);
			y = i * (CELL_ROW + 1);
			cell[i][j].set_coordinate(x, y);
		}
	}
}

void Map::display_map_frame() {
	for (int i = 0; i < MAP_ROW; i++) {
		for (int j = 0; j < MAP_COLUMN; j++) {
			cell[i][j].display_cell_frame();
		}
	}
	set_cursor_position((CELL_COLUMN + 1) * MAP_COLUMN + 1, 0);
	for (int i = 0; i < ROAD_WIDTH; i++) {
		cout << "#";
	}
	set_cursor_position((CELL_COLUMN + 1) * MAP_COLUMN + 1, MAP_HEIGHT - 1 );
	for (int i = 0; i < ROAD_WIDTH; i++) {
		cout << "#";
	}
}

void Map::generate_zombie(int step) {
	if (step % ZOMBIE_APPEAR_STEP)
		return;
	int r = rand() % MAP_ROW;
	int type = rand() % ZOMBIE_TYPE;
	cell[r][MAP_COLUMN].place_zombie(type);
}