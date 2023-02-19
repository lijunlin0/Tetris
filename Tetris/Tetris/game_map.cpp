#pragma once
#include"game_map.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include<cmath>
#include"block.h"
#include"time.h"

game_map::game_map()
{
	gap = BLOCK_MOVE_GAP;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			data[i][j] = 0;
		}
	 }
	create_block();
}

//消除
void game_map::eliminate()
{
	int y = 0;
	if (m_block->is_move == false)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			int is_eli = true;
			for (int j = 0; j < HEIGHT; j++)
			{
				if (data[i][j] < 0)
				{
					is_eli = false;
					break;
				}
			}
			//如果能消除
			if (is_eli)
			{
				//消除
				for (int x = 0; x < WIDTH; x++)
				{
					y = i - 1;
					data[x][y] == 0;
				}
			}

		}
	}
}

//生成方块
void game_map::create_block()
{
	int num = rand() % COLOR_COUNT+1;
	num = 2;
	m_block = new block(num,this);
}

//更新
void game_map::update()
{
	//1.更新掉落中的方块
	//2.清空地图
	//3.根据数据绘制格子
	draw();
	if (time::update_ms - move_ms < gap)
	{
		return;
	}
	move_ms = time::update_ms;
	m_block->move_down();
}

//位置是否合法
bool game_map::isvalid(int x,int y)
{
	return x > 2 && x<WIDTH+2&& y>2 && y < HEIGHT+2;
}


COLORREF game_map::value_to_color(int value)
{
	switch (value)
	{
	case 1:return BLUE;
	case 2:return GREEN;
	case 3:return RED;
	case 4:return CYAN;
	case 5:return YELLOW;
	case 6:return BROWN;
	case 7:return  MAGENTA;
	}
}


//尝试
void game_map::try_block_rotate()
{
	if (m_block->can_rotate())
	{
		m_block->rotate();
	}
}
void game_map::try_block_move_left()
{
	if (m_block->can_move_left())
	{
		m_block->move_left();
	}
}
void game_map::try_block_move_right()
{
	if (m_block->can_move_right())
	{
		m_block->move_right();
	}
}
void game_map::try_block_move_down()
{
	if (m_block->can_move_down())
	{
		m_block->move_down();
	}
}

int game_map::get_value(int x, int y)
{
	return data[x][y];
}
void game_map::set_value(int x, int y, int value)
{
	data[x][y] = value;
}
//方块值抹除
void game_map::reset()
{
	setfillcolor(BLACK);
	int left_x = (0 + offset_x) * BLOCK_SIZE;
	int up_y = (0 + offset_y) * BLOCK_SIZE;
	int right_x = (WIDTH + offset_x) * BLOCK_SIZE;
	int down_y = (HEIGHT + offset_y) * BLOCK_SIZE;
	solidrectangle(left_x, up_y, right_x, down_y);
}

//画小方块
void game_map::draw_cell(int x, int y, int value)
{
	COLORREF color = value_to_color(value);
	setfillcolor(value_to_color(color));
	int left_x = (x + offset_x) * BLOCK_SIZE;
	int up_y = (y + offset_y) * BLOCK_SIZE;
	int right_x = (x + 1 + offset_x) * BLOCK_SIZE;
	int down_y = (y + 1 + offset_y) * BLOCK_SIZE;
	solidrectangle(left_x, up_y, right_x, down_y);
}

void game_map::draw()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (data[i][j] > 0)
			{
				draw_cell(i, j, data[i][j]);
			}
		}
	}
	m_block->draw();
}