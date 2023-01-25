#include<iostream>
#include <graphics.h>
#include <conio.h>
#include <thread>
#include"game_map.h"
#include"time.h"

using namespace std;

long long time::update_ms = 0;

void init_ui()
{
	int size = game_map::BLOCK_SIZE;
	//��ͼ���
	COLORREF color = RGB(105, 105, 105);
	setfillcolor(color);
	solidrectangle(size, size, 13 * size, 23 * size);

	//��ͼ�ڿ�
	setfillcolor(BLACK);
	solidrectangle(2 * size, 2 * size, 12 * size, 22 * size);

	//next���
	setfillcolor(color);
	solidrectangle(14 * size, 3 * size, 20 * size, 9 * size);

	setfillcolor(BLACK);
	solidrectangle(15 * size, 4 * size, 19 * size, 8 * size);
}

int main()
{
	int size = game_map::BLOCK_SIZE;
	int screen_width = 21 * size;
	int screen_height = 24 * size;
	
	initgraph(756, 864);
	init_ui();
	game_map m;
	while (true)
	{
		long long current = time::current_time();
		if (current - time::update_ms < time::frame_ms)
		{
			continue;
		}
		m.update();
	}
}