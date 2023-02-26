#pragma once
#include"game_map.h"
#include<utility>

class block
{
public:
	static const int width = 4;
	static const int height = 4;
private:
	int data[width][height];
	int m_type;
	int m_color;
	int block_x = 3;
	int block_y = 0;
	game_map* m;
	//һ�����ܷ���ת
	bool can_rotate_I();
	//һ������ת
	void rotate_I();
public:
	block(int type,int color,game_map*map);
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
	//��������ڵ�ͼ��
	void put_to_map();
};
