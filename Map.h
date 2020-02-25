#include "common.h"
#include "Plant.h"
#include "Zombie.h"
class Cell {
private:
	int x, y;//the coordinate of the cell's top left corner
public:
	Cell();
	Plant* plant;
	Zombie* zombie[CELL_ROW];
	void set_coordinate(int x, int y);
	void display_cell_frame();
	void build_plant(int type, int step);
	int place_zombie(int type);
	void display_content();
};

class Map{
private:

public:
	Cell** cell;
	Map();
	void display_map_frame();
	void generate_zombie(int step);
};

