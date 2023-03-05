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

//消除空行
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


//消除
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

//生成方块
void game_map::create_block()
{
	//游戏初始化时，需要生成一个方块
	if (m_block_next == nullptr)
	{
		int type = rand() % COLOR_COUNT + 1;
		int color = rand() % COLOR_COUNT + 1;
		m_block_next = new block(type, color, this);
	}
	//将下一个方块交换给当前方块
	m_block = m_block_next;
	//生成下一个方块
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

//游戏结束
void game_map::game_end()
{
	int x = 13 * BLOCK_SIZE / 2;
	int y = 23 * BLOCK_SIZE / 2;
	//字体颜色为粉色
	COLORREF color = RGB(255, 105, 180);
	settextcolor(color);
	settextstyle(48, 0, _T("Consolas"));
	int w = textwidth(" GAME OVER !");
	int h = textheight(" GAME OVER !");
	//显示字体 "GAME OVER!"
	outtextxy(x - w / 2, y - h / 2, " GAME OVER !");
	is_over = true;
}

//显示分数
void game_map::draw_score()
{
	int x = 16 * BLOCK_SIZE;
	int y = 20 * BLOCK_SIZE;
	//字体颜色为粉色
	settextcolor(WHITE);
	settextstyle(48, 0, _T("Consolas"));
	int w = textwidth("SCORE:");
	int h = textheight("SCORE:");
	//显示字体 "GAME OVER!"
	string str ="SCORE:" + to_string(score);
	outtextxy(x - w / 2-6, y - h / 2, str.c_str());
}

void game_map::draw_next()
{
	int x = 16 * BLOCK_SIZE;
	int y = 2 * BLOCK_SIZE;
	//字体颜色为粉色
	settextcolor(WHITE);
	settextstyle(48, 0, _T("Consolas"));
	int w = textwidth("NEXT:");
	int h = textheight("NEXT:");
	//显示字体 "GAME OVER!"
	outtextxy(x - w / 2-16, y - h / 2,"NEXT:");
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
	try_block_move_down();
	draw_score();
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
	case 1:return GREEN;
	case 2:return RED;
	case 3:return CYAN;
	case 4:return YELLOW;
	case 5:return BROWN;
	case 6:return MAGENTA;
	case 7:return BLUE;
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
//方块值抹除
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

//画小方块
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