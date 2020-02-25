#include "Player.h"
#include "common.h"
Player::Player() {
	score = 0;
	sunshine = 50;
}

void Player::display_frame() {
	set_cursor_position(0, MAP_HEIGHT + 2);
	for (int i = 0; i < MAP_WIDTH + ROAD_WIDTH; i++) {
		cout << "=";
	}
	set_cursor_position(0, MAP_HEIGHT + 3);
	cout << "[商店] 阳光总数：";
	set_cursor_position((MAP_WIDTH + ROAD_WIDTH) / 2, MAP_HEIGHT + 3);
	cout << "[得分] ";
	set_cursor_position(0, MAP_HEIGHT + 4);
	for (int i = 0; i < MAP_WIDTH + ROAD_WIDTH; i++) {
		cout << "-";
	}
	sunshine_position_x = 17;
	sunshine_position_y = MAP_HEIGHT + 3;
	score_position_x = (MAP_WIDTH + ROAD_WIDTH) / 2 + 7;
	score_position_y = MAP_HEIGHT + 3;
}

void Player::display_score() {
	set_cursor_position(score_position_x, score_position_y);
	cout << "     ";
	set_cursor_position(score_position_x, score_position_y);
	cout << score;
}

void Player::display_sunshine() {
	set_cursor_position(sunshine_position_x, sunshine_position_y);
	cout << "      ";
	set_cursor_position(sunshine_position_x, sunshine_position_y);
	cout << sunshine;
}

void Player::natural_sunshine(int step) {
	if (step % NATURAL_STEP)
		return;
	sunshine_change(50);
	display_sunshine();
}

void Player::sunshine_change(int diff) {
	sunshine += diff;
}

void Player::score_increase(int diff) {
	score += diff;
}