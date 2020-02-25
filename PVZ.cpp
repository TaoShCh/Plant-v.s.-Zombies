#include "Map.h"
#include "Shop.h"

int main()
{
	//game_begin();
	game_init();
	Map map;
	map.display_map_frame();
	Shop shop;
	shop.display_goods();
	Player player;
	player.display_frame();
	player.display_score();
	player.display_sunshine();
	int step = 1, dead_flag = 0;
	while (1) {
		Sleep(50);
		step = (step + 1) % 10000000;
		if (_kbhit()) {
			shop.get_key(&map, &player, step);
		}
		player.natural_sunshine(step);
		map.generate_zombie(step);
		for (int i = 0; i < MAP_ROW; i++) {
			for (int j = 0; j < MAP_COLUMN + 1; j++) {
				for (int k = 0; k < CELL_ROW; k++) {
					Zombie* zombie = map.cell[i][j].zombie[k];
					if (zombie != NULL) {
						if (zombie->move(step, &map))
							dead_flag = 1;
						zombie->display();
					}
				}
				Plant* plant = map.cell[i][j].plant;
				if (plant != NULL) {
					plant->display();
				}
			}
		}
		for (int i = 0; i < MAP_ROW; i++) {
			for (int j = 0; j < MAP_COLUMN + 1; j++) {
				Plant* plant = map.cell[i][j].plant;
				if (plant != NULL) {
					plant->function(step, &player, &map);
				}
			}
		}
		if (dead_flag) {
			break;
		}
	}
	game_over();
	return 0;
}

