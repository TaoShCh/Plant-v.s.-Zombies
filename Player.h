#include "common.h"
class Player
{
	friend class Shop;
private:
	int score;
	int sunshine;
	int score_position_x, score_position_y;
	int sunshine_position_x, sunshine_position_y;
public:
	Player();
	void display_frame();
	void display_score();
	void display_sunshine();
	void natural_sunshine(int step);
	void score_increase(int diff);
	void sunshine_change(int diff);
};

