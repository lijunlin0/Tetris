#pragma once
#include<windows.h>
#include"block.h"

class game_map
{
public:
	static const char KEY_W = 0x57;
	static const char KEY_A = 0x41;
	static const char KEY_S = 0x53;
	static const char KEY_D = 0x44;
	//方块大小36*36
	static const int BLOCK_SIZE = 36;
	static const int WIDTH = 10;
	static const int HEIGHT = 20;
	static const int COLOR_RED = 1;
	static const int COLOR_GREEN = 2;
	//空白
	static const int BLANK = 0;
	//砖块身体
	static const int BODY = 1;
	//砖块障碍物
	static const int BLOCK = 2;
	
public:
	block* m_block;
	static int data[WIDTH][HEIGHT];
	game_map();
	//更新
	void update();
	//方块值抹除
	void reset();
	bool isvalid(int x,int y);
	COLORREF color = RGB(255, 105, 180);
	COLORREF value_to_color(int value);
	//生成方块
	void create_block();
	void try_block_rotate();
	void try_block_move_left();
	void try_block_move_right();
	void try_block_move_down();

	int get_value(int x, int y);
	void set_value(int x, int y,int value);
};
