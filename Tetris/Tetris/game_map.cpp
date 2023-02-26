#pragma once
#include"game_map.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include<cmath>
#include"block.h"
#include"time.h"
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

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

//��������
void game_map::delete_blank(vector<int> lines)
{
	for (int index = 0; index < lines.size(); index++)
	{
		int y = lines[index];
		for (int j = y; j > 0; j--)
		{
			for (int i = 0; i < WIDTH; i++)
			{
				data[i][j] = data[i][j - 1];
			}
		}
		for (int a = 0; a < WIDTH; a++)
		{
			data[a][0] = 0;
		}
	}
}


//����
void game_map::eliminate()
{
	vector<int> lines;
	for (int j = 0; j < HEIGHT; j++)
	{
		bool find = true;
		for (int i = 0; i < WIDTH; i++)
		{
			if (data[i][j] == 0)
			{
				find = false;
				break;
			}
		}
		if (find == true)
		{
			play_sound();
			lines.push_back(j);
			for (int a = 0; a < WIDTH; a++)
			{
				data[a][j] = 0;
			}
		}
	}
	delete_blank(lines);
}

//���ɷ���
void game_map::create_block()
{
	int type = rand() % COLOR_COUNT+1;
	int color= rand() % COLOR_COUNT;
	m_block = new block(type,color,this);
}

//����
void game_map::update()
{
	//1.���µ����еķ���
	//2.��յ�ͼ
	//3.�������ݻ��Ƹ���
	draw();
	if (time::update_ms - move_ms < gap)
	{
		return;
	}
	move_ms = time::update_ms;
	try_block_move_down();
}

//λ���Ƿ�Ϸ�
bool game_map::isvalid(int x,int y)
{
	return x > 2 && x<WIDTH+2&& y>2 && y < HEIGHT+2;
}


COLORREF game_map::value_to_color(int value)
{
	switch (value)
	{
	case 1:return GREEN;
	case 2:return RED;
	case 3:return CYAN;
	case 4:return YELLOW;
	case 5:return BROWN;
	case 6:return  MAGENTA;
	case 7:return BLUE;
	}
}


//����
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
	else
	{
		m_block->put_to_map();
		delete m_block;
		eliminate();
		create_block();
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
//����ֵĨ��
void game_map::reset()
{
	setfillcolor(BLACK);
	int left_x = (0 + offset_x) * BLOCK_SIZE;
	int up_y = (0 + offset_y) * BLOCK_SIZE;
	int right_x = (WIDTH + offset_x) * BLOCK_SIZE;
	int down_y = (HEIGHT + offset_y) * BLOCK_SIZE;
	solidrectangle(left_x, up_y, right_x, down_y);
}

//��С����
void game_map::draw_cell(int x, int y, int color)
{
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
void game_map::play_sound()
{
	int audio = rand() % 2;
	switch (audio)
	{
	case 0:PlaySound(("C:/D/GitHub/Tetris/Tetris/Tetris/sound/eliminate1.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	case 1:PlaySound(("C:/D/GitHub/Tetris/Tetris/Tetris/sound/eliminate2.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
	}
}