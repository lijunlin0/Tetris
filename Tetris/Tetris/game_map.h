#pragma once
#include<windows.h>
#include<vector>
class block;
class game_map
{
public:
	COLORREF color_a;
	static const char KEY_W = 0x57;
	static const char KEY_A = 0x41;
	static const char KEY_S = 0x53;
	static const char KEY_D = 0x44;
	//�����С36*36
	static const int BLOCK_SIZE = 36;
	static const int WIDTH = 10;
	static const int HEIGHT = 20;
	//�հ�
	static const int BLANK = 0;
	//ש������
	static const int BODY = 1;
	//ש���ϰ���
	static const int BLOCK = 2;
	static const int COLOR_COUNT=7;
	const int offset_x = 2;
	const int offset_y = 2;
	const int BLOCK_MOVE_GAP = 500;
	const int BLOCK_MOVE_GAP_MIN = 100;
	const int BLOCK_MOVE_GAP_REDUCE = 10;

	long long move_ms;
	int gap;
	int data[WIDTH][HEIGHT];
	block* m_block;
	block* m_block_next;
public:
	//����
	int score;
	bool is_over = false;
	game_map();
	//����
	void update();
	//����ֵĨ��
	void reset();
	bool isvalid(int x,int y);
	COLORREF value_to_color(int value);
	//���ɷ���
	void create_block();
	void try_block_rotate();
	void try_block_move_left();
	void try_block_move_right();
	void try_block_move_down();

	int get_value(int x, int y);
	void set_value(int x, int y,int value);
	//��С����
	void draw_cell(int x,int y,int color);
	void draw();

	//����
	void eliminate();
	//��������
	void delete_blank(std::vector<int> lines);
	void play_sound();
	//��Ϸ����
	void game_end();
	//��ʾ����
	void draw_score();
	void draw_next();
};
