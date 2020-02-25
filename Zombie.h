#include "common.h"
class Map;
class Zombie
{
protected:
	int hp;
	int move_interval;
	int attack;
	string name;
	int type;
	int x, y;
public:
	Zombie(int hp, int move_interval, int attack, int type, string name);
	void set_xy(int x, int y);
	int get_hp();
	int move(int step, Map *map);
	void display();
	void under_attack(int damage);
	void clear();
};

class Normal_zombie : Zombie {
public:
	Normal_zombie();
};

class Roadblock_zombie : Zombie {
public:
	Roadblock_zombie();
};