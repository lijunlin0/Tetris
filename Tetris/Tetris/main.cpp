#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <thread>
#include"map.h"

using namespace std;

int main()
{
	int screen_width = 21 * game_map::BLOCK_SIZE;
	int screen_height = 24 * game_map::BLOCK_SIZE;
	initgraph(756, 864);
	COLORREF color = RGB(105, 105, 105);
	setfillcolor(color);
	solidrectangle(36, 36, 468, 828);
	setfillcolor(BLACK);
	solidrectangle(72, 72, 436, 796);
	setfillcolor(color);
	solidrectangle(504, 108, 720, 324);
	setfillcolor(BLACK);
	solidrectangle(540, 144, 684, 288);

	while (true)
	{

	}
}