#include "common.h"
#include "Player.h"

class Map;
class Plant
{
protected:
	int hp;
	int type;
	string name;
	int x, y;
public:
	int birth_step;
	Plant(int hp, int type, string name);
	void set_xy(int x, int y);
	int get_hp();
	void display();
	void under_attack(int damage);
	virtual void function(int step, Player *player, Map *m) = 0;
	void clear();
};

class Sunflower :Plant {
private:
public:
	Sunflower();
	void function(int step, Player* player, Map *m);
};

class Peabullet {
private:
	int x, y;
public:
	Peabullet(int x, int y);
	void display();
	void clear();
	void move(int step, Map *map);
	bool whether_hit(Map *map, Player* player);
	bool outrange();
};

class Peashooter : public Plant {
protected:
	Peabullet* bullet[MAX_BULLET];
public:
	Peashooter();
	void generate_bullet();
	virtual void function(int step, Player* player, Map *map);
};

class Double_Peashooter : Peashooter {
public:
	Double_Peashooter();
	void function(int step, Player* player, Map* map);
};