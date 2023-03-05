#pragma once
#include"game_map.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include<cmath>
#include<string>
#include"block.h"
#include"time.h"
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

game_map::game_map()
{
	gap = BLOCK_MOVE_GAP;
	move_ms = time::update_ms;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			data[i][j] = 0;
		}
	 }
	score = 0;
	create_block();
	draw_next();
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
			score += 1;
			gap -= BLOCK_MOVE_GAP_REDUCE;
			if (gap < BLOCK_MOVE_GAP_MIN)
			{
				gap = BLOCK_MOVE_GAP_MIN;
			}
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
	//��Ϸ��ʼ��ʱ����Ҫ����һ������
	if (m_block_next == nullptr)
	{
		int type = rand() % COLOR_COUNT + 1;
		int color = rand() % COLOR_COUNT + 1;
		m_block_next = new block(type, color, this);
	}
	//����һ�����齻������ǰ����
	m_block = m_block_next;
	//������һ������
	int type = rand() % COLOR_COUNT + 1;
	int color = rand() % COLOR_COUNT + 1;
	m_block_next = new block(type, color, this);

    if (!m_block->can_put())
	{
		while (!m_block->can_put())
		{
			m_block->move_up();
		}
		reset();
		draw();
		game_end();
	}
}

//��Ϸ����
void game_map::game_end()
{
	int x = 13 * BLOCK_SIZE / 2;
	int y = 23 * BLOCK_SIZE / 2;
	//������ɫΪ��ɫ
	COLORREF color = RGB(255, 105, 180);
	settextcolor(color);
	settextstyle(48, 0, _T("Consolas"));
	int w = textwidth(" GAME OVER !");
	int h = textheight(" GAME OVER !");
	//��ʾ���� "GAME OVER!"
	outtextxy(x - w / 2, y - h / 2, " GAME OVER !");
	is_over = true;
}

//��ʾ����
void game_map::draw_score()
{
	int x = 16 * BLOCK_SIZE;
	int y = 20 * BLOCK_SIZE;
	//������ɫΪ��ɫ
	settextcolor(WHITE);
	settextstyle(48, 0, _T("Consolas"));
	int w = textwidth("SCORE:");
	int h = textheight("SCORE:");
	//��ʾ���� "GAME OVER!"
	string str ="SCORE:" + to_string(score);
	outtextxy(x - w / 2-6, y - h / 2, str.c_str());
}

void game_map::draw_next()
{
	int x = 16 * BLOCK_SIZE;
	int y = 2 * BLOCK_SIZE;
	//������ɫΪ��ɫ
	settextcolor(WHITE);
	settextstyle(48, 0, _T("Consolas"));
	int w = textwidth("NEXT:");
	int h = textheight("NEXT:");
	//��ʾ���� "GAME OVER!"
	outtextxy(x - w / 2-16, y - h / 2,"NEXT:");
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
	draw_score();
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
	case 6:return MAGENTA;
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
	left_x = (13 + offset_x) * BLOCK_SIZE;
	up_y = (2 + offset_y) * BLOCK_SIZE;
	right_x = (17 + offset_x) * BLOCK_SIZE;
	down_y = (6 + offset_y) * BLOCK_SIZE;
	solidrectangle(left_x, up_y, right_x, down_y);
}

//��С����
void game_map::draw_cell(int x, int y, int color)
{
    setfillcolor(value_to_color(color));
	setlinecolor(WHITE);
	int left_x = (x + offset_x) * BLOCK_SIZE;
	int up_y = (y + offset_y) * BLOCK_SIZE;
	int right_x = (x + 1 + offset_x) * BLOCK_SIZE;
	int down_y = (y + 1 + offset_y) * BLOCK_SIZE;
	fillrectangle(left_x, up_y, right_x, down_y);
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
	m_block_next->draw_next();

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