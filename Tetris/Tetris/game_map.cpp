#pragma once
#include"game_map.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>

game_map::game_map()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; i++)
		{
			data[i][j] = 0;
		}
	 }
}

//生成方块
void game_map::create_block()
{
	
	
}

//更新
void game_map::update()
{
	//1.更新掉落中的方块
	//2.清空地图
	//3.根据数据绘制格子

}

//位置是否合法
bool game_map::isvalid(int x,int y)
{
	return x > 2 && x<WIDTH+2&& y>2 && y < HEIGHT+2;
}


COLORREF value_to_color(int value)
{
	COLORREF color = RGB(255, 105, 180);
	switch (value)
	{
	case 0:return BLACK;
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
	m_block->reset();
}