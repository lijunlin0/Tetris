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
	//�ܷ�����
	bool can_move_left();
	//�ܷ�����
	bool can_move_right();
	//�ܷ�����
	bool can_move_down();
	//�ܷ���ת
	bool can_rotate();
	//����
	void move_left();
	//����
	void move_right();
	//����
	void move_down();
	//��ת
	void rotate();
	//��ȡ��ת���λ��
	std::pair<int,int> get_rotate_position(int x,int y);
	//��ȡ��ת�ϰ�λ��
	std::pair<int, int> get_obstacle_position(int x, int y);
	void draw();
	//������������data
	void set_data();
};
