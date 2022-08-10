#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <random>
#include <map>
using namespace std;
class car {
public:
	int _x, _y;
	string image;
	car() {
		_y = 5;
		_x = 20;
		image = ">[]>";
	}
};
car C1;
int g_count = 3;

void clrscr() {
	system("CLS");
}
void gotoXY(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x,y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void DisplayScores() {
	gotoXY(20, 40);
	cout << "SO XE DAM TRUNG : " << g_count;
}
void DisplaySreen() {
	int x = 10;
	int y = 3;

	for (int i = 0; i < 40; i++) {
		gotoXY(x + i, y);
		cout << "=";
	}
	
	for (int i = 0; i < 40; i++) {
		gotoXY(x + i, y + 6);
		cout << "=";
	}

	gotoXY(10, 10);
	cout << "SO MANG : " << g_count;
}
void DisplayGameOver() {
	int x, y;
	x = 15;
	y = 5;
	for (int i = 0; i < 40; i++) {
		gotoXY(x + i, y);
		cout << "=";
	}
	for (int i = 0; i < 5; i++) {
		gotoXY(x, y + i + 1);
		cout << "|";
		gotoXY(x + 39, y + i + 1);
		cout << "|";
	}
	for (int i = 0; i < 40; i++) {
		gotoXY(x + i, y + 5);
		cout << "=";
	}
	gotoXY(25, 7);
	cout << "G A M E   O V E R !!";
}
void Handle() {

	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case 'w': C1._y--; break;
		case 's': C1._y++; break;
		case 'd': C1._x++; break;
		case 'a': C1._x--; break;
		default: break;
		}
	}
}
bool CheckDie(vector<pair<int, int>>& Threat) {
	for (auto& x : Threat) {
		if (x.first == C1._x && x.second == C1._y) return true;
	}
	return false;
}
void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int status = 1;
	vector<pair<int, int>> Threat;
	srand(time(NULL));
	pair<int, int> x;
	map<pair<int, int>, bool> Check;
	int delay = 5;
	while (1) {
		clrscr();
		if (status == 1) {
			if (Threat.size() < 15 && delay == 0) {
				x.second = rand() % 7 + 3;
				x.first = 50;
				Threat.push_back(x);
				delay = 5;
			}
			delay--;
			DisplaySreen();
			Handle();
			gotoXY(C1._x, C1._y);
			TextColor(9);
			cout << C1.image;
			TextColor(2);
			for (int i = 0; i < Threat.size(); i++) {
				if (Threat[i].first < 10) {
					Threat[i].first = 50;
					Threat[i].second = rand() % 7 + 3;
					gotoXY(Threat[i].first, Threat[i].second);
					cout << "X";
				}
				else
				{
					gotoXY(Threat[i].first, Threat[i].second);
					cout << "X";

					Threat[i].first -= 2;
				}
			}
			TextColor(7);

			g_count -= (CheckDie(Threat) ? 1 : 0);

			if (g_count == 0) {
				status = 0;
			}
		}
		else
		{
			DisplayGameOver();
			Sleep(5000);
			return 0;
		}
		Sleep(50);
	}
	return 0;
}
