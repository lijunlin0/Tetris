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

	//地图尺寸：21*24 （宽：21*36 * 高：24*36）
	
	//地图外框
	COLORREF color = RGB(105, 105, 105);
	setfillcolor(color);
	solidrectangle(size, size, 13 * size, 23 * size);

	//地图内框
	setfillcolor(BLACK);
	solidrectangle(2 * size, 2 * size, 12 * size, 22 * size);

	//next外框
	setfillcolor(color);
	solidrectangle(14 * size, 3 * size, 20 * size, 9 * size);

	setfillcolor(BLACK);
	solidrectangle(15 * size, 4 * size, 19 * size, 8 * size);
}

int main()
{
	int size =game_map::BLOCK_SIZE;
	int screen_width = 21 * size;
	int screen_height = 24 * size;
	
	initgraph(756, 864);
	init_ui();
	game_map m;
	ExMessage msg;//创建消息变量
	while (true)
	{
		long long current = time::current_time();
		if (current - time::update_ms < time::frame_ms)
		{
			continue;
		}
		m.reset();
		bool b = peekmessage(&msg, EX_KEY);
		if (b && msg.message == WM_KEYDOWN)
		{
			if (msg.vkcode == game_map::KEY_W)
			{
				m.try_block_rotate();
			}
			else if (msg.vkcode == game_map::KEY_A)
			{
				m.try_block_move_left();
			}
			else if (msg.vkcode == game_map::KEY_S)
			{
				m.try_block_move_down();
			}
			else if (msg.vkcode == game_map::KEY_D)
			{
				m.try_block_move_right();
			}
		}
		m.update();
	}
}