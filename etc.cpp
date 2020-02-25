#include "common.h"

//x means column, y means row
void set_cursor_position(int x, int y) {
	HANDLE stdhd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x, y };
	SetConsoleCursorPosition(stdhd, pos);
}

void set_text_color(int attribute) {
	HANDLE stdhd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(stdhd, attribute);
}

void game_init() {
	SetConsoleTitleA("Plants vs. Zombies");
	HANDLE stdhd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(stdhd, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(stdhd, &CursorInfo);
	SMALL_RECT rc;
	rc.Left = 0;
	rc.Top = 0;
	rc.Right = 100;
	rc.Bottom = 90;
	SetConsoleWindowInfo(stdhd, TRUE, &rc);
	srand((unsigned)time(NULL));
}

int cellx(int x) {
	return x / (CELL_COLUMN + 1);
}

int celly(int y) {
	return y / (CELL_ROW + 1);
}

void game_begin() {
	cout << "This Plants vs. Zombies game is a project in Advanced Progamming 2019 autumn course" << endl;
	cout << "Developed by Tao Shaocheng @ NJU" << endl << endl;
	Sleep(5000);
	system("cls");
}

void game_over() {
	system("cls");
	cout << "Game over" << endl;
	cout << "Your brain is eaten" << endl;
}