#pragma once
#include"game_map.h"
#include<utility>

class block
{
public:
	static const int width = 4;
	static const int height = 4;
	int data[width][height];
	int m_value;
	int block_x = 3;
	int block_y = 0;
	bool is_move;
	game_map*m;
	block(int value,game_map*map);
	//能否左移
	bool can_move_left();
	//能否右移
	bool can_move_right();
	//能否下移
	bool can_move_down();
	//能否旋转
	bool can_rotate();
	//左移
	void move_left();
	//右移
	void move_right();
	//下移
	void move_down();
	//旋转
	void rotate();
	//获取旋转后的位置
	std::pair<int,int> get_rotate_position(int x,int y);
	//获取旋转障碍位置
	std::pair<int, int> get_obstacle_position(int x, int y);
	void draw();
	//根据数字设置data
	void set_data();
};
