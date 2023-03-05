#include"block.h"
#include"game_map.h"
#include<vector>
#include<iostream>
using namespace std;

block::block(int type,int color,game_map*map)
{
	m_type = type;
	m_color = color;
	m=map;
	set_data();
	cout << m_type << endl;
}

//根据数字设置data
void block::set_data()
{
	//一字形
	if (m_type == 1)
	{
		data[0][1] = m_color; data[1][1] = m_color; data[2][1] = m_color; data[3][1] = m_color;
	}
	//反7
	if (m_type == 2)
	{
		data[1][0] = m_color; data[1][1] = m_color; data[1][2] = m_color; data[2][0] = m_color;
	}
	//7
	if (m_type == 3)
	{
		data[0][0] = m_color; data[1][0] = m_color; data[1][1] = m_color; data[1][2] = m_color;
	}
	//z
	if (m_type == 4)
	{
		data[0][0] = m_color; data[1][0] = m_color; data[1][1] = m_color; data[2][1] = m_color;
	}
	//反z
	if (m_type == 5)
	{
		data[1][0] = m_color; data[2][0] = m_color; data[0][1] = m_color; data[1][1] = m_color;
	}
	//土
	if (m_type == 6)
	{
		data[1][0] = m_color; data[0][1] = m_color; data[1][1] = m_color; data[2][1] = m_color;
	}
	//田 
	if (m_type == 7)
	{
		data[1][1] = m_color; data[2][1] = m_color; data[1][2] = m_color; data[2][2] = m_color;
	}
}

//能否左移
bool block::can_move_left()
{
	for (int i = 0; i < block::width; i++)
	{
		for (int j = 0; j < block::height; j++)
		{
			if (data[i][j] == m_color)
			{
				//左边超出边界
				if (block_x + i - 1 < 0)
				{
					return false;
				}
				//左边为障碍
				else if (m->get_value(block_x + i - 1,block_y + j) > 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}
//能否右移
bool block::can_move_right()
{
	for (int i = 0; i < block::width; i++)
	{
		for (int j = 0; j < block::height; j++)
		{
			if (data[i][j] == m_color)
			{
				//右边超出边界
				if ((block_x + i + 1) > (game_map::WIDTH-1))
				{
					return false;
				}
				//右边为障碍
				else if (m->get_value(block_x + i + 1, block_y + j) > 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}
//能否下移
bool block::can_move_down()
{
	for (int i = 0; i < block::width; i++)
	{
		for (int j = 0; j < block::height; j++)
		{
			if (data[i][j] == m_color)
			{
				//下方为边界
				if ((block_y + j + 1) > (game_map::HEIGHT-1))
				{
					return false;
				}
				//下方为障碍
				else if (m->get_value(block_x + i, block_y + j + 1) > 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

//获取旋转后的位置
std::pair<int, int> block::get_rotate_position(int x, int y)
{
	if (x == 0 && y == 0) { return std::pair<int, int>(2, 0); }
	else if (x == 1 && y == 0) { return std::pair<int, int>(2, 1); }
	else if (x == 2 && y == 0) { return std::pair<int, int>(2, 2); }
	else if (x == 0 && y == 1) { return std::pair<int, int>(1, 0); }
	else if (x == 1 && y == 1) { return std::pair<int, int>(1, 1); }
	else if (x == 2 && y == 1) { return std::pair<int, int>(1, 2); }
	else if (x == 0 && y == 2) { return std::pair<int, int>(0, 0); }
	else if (x == 1 && y == 2) { return std::pair<int, int>(0, 1); }
	else if (x == 2 && y == 2) { return std::pair<int, int>(0, 2); }
}

//获取旋转障碍位置
std::pair<int, int> block:: get_obstacle_position(int x, int y)
{
	if (x == 0 && y == 0) { return std::pair<int, int>(1, 0); }
	else if (x == 1 && y == 0) { return std::pair<int, int>(2, 0); }
	else if (x == 2 && y == 0) { return std::pair<int, int>(2, 1); }
	else if (x == 0 && y == 1) { return std::pair<int, int>(0, 0); }
	else if (x == 1 && y == 1) { return std::pair<int, int>(1, 1); }
	else if (x == 2 && y == 1) { return std::pair<int, int>(2, 2); }
	else if (x == 0 && y == 2) { return std::pair<int, int>(0, 1); }
	else if (x == 1 && y == 2) { return std::pair<int, int>(0, 2); }
	else if (x == 2 && y == 2) { return std::pair<int, int>(1, 2); }
}

bool block::can_rotate_I()
{
	vector<pair<int, int>> positions;
	positions.push_back(pair<int, int>(0,0));
	positions.push_back(pair<int, int>(1,0));
	positions.push_back(pair<int, int>(0,1));
	positions.push_back(pair<int, int>(1,1));
	positions.push_back(pair<int, int>(2,1));
	positions.push_back(pair<int, int>(3,1));
	positions.push_back(pair<int, int>(1,2));
	positions.push_back(pair<int, int>(1,3));
	positions.push_back(pair<int, int>(2,2));
	positions.push_back(pair<int, int>(3,2));
	positions.push_back(pair<int, int>(2,3));
	positions.push_back(pair<int, int>(3,3));
	for (int i = 0; i < positions.size(); i++)
	{
		int x = positions[i].first+block_x;
		int y = positions[i].second+block_y;
		if (x < 0 || x >= m->WIDTH || y < 0 || y >= m->HEIGHT)
		{
			return false;
		}
		if (m->get_value(x, y) > 0)
		{
			return false;
		}
	}
	return true;
}

//能否旋转
bool block::can_rotate()
{
	//如果是田字形
	if (m_type == 7)
	{
		return false;
	}
	//如果是一字形
	if (m_type == 1)
	{
		return can_rotate_I();
	}

	int x = 0;
	int y = 0;
	//其他方块
	for (int i = 0; i < width-1; i++)
	{
		for (int j = 0; j < height-1; j++)
		{
			if (data[i][j] == m_color)
			{
				continue;
			}
			if (i == 1 && j == 1)
			{
				continue;
			}
			std::pair<int, int> position = get_rotate_position(i, j);
			x = position.first+block_x;
			y = position.second+block_y;
			
			if (x < 0 || x >= m->WIDTH || y < 0 || y >= m->HEIGHT)
			{
				return false;
			}

			if (m->get_value(x,y)>0)
			{
				return false;
			}
			position = get_obstacle_position(i, j);
			x = position.first + block_x;
			y = position.second + block_y;
			if (m->get_value(x,y)>0)
			{
				return false;
			}
		}
	}
	return true;
}

//上移
void block::move_up()
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			data[i][j] = data[i][j+1];
		}
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			data[i][3] = 0;
		}
	}
}

//左移
void block::move_left()
{
	block_x--;
}
//右移
void block::move_right()
{
	block_x++;
}
//下移
void block::move_down()
{
	block_y++;
}

//一字形旋转
void block::rotate_I()
{
	if (data[0][1] == m_color)
	{
		data[0][1] = 0;
		data[2][1] = 0;
		data[3][1] = 0;
		data[1][0] = m_color;
		data[1][2] = m_color;
		data[1][3] = m_color;
	}
	else
	{
		data[0][1] = m_color;
		data[2][1] = m_color;
		data[3][1] = m_color;
		data[1][0] = 0;
		data[1][2] = 0;
		data[1][3] = 0;
	}
}

//旋转
void block::rotate()
{
	if (m_type == 1)
	{
		rotate_I();
		return;
	}
	int temp[width][height];
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			temp[i][j] = data[i][j];
		}
	}
	for (int i = 0; i < width-1; i++)
	{
		for (int j = 0; j < height-1; j++)
		{
			std::pair<int, int> position = get_rotate_position(i, j);
			int x = position.first;
			int y = position.second;
			data[x][y] = temp[i][j];
		}
	}
}

void block::draw()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (data[i][j] == m_color)
			{
				m->draw_cell(i + block_x, j + block_y, m_color);
			}
		}
	}
}
//将方块放在地图中
void block::put_to_map()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (data[i][j] == m_color)
			{
				m->data[i + block_x][j + block_y] = m_color;
			}
		}
	}
}
//能否放在地图上
bool block::can_put()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (data[i][j] == m_color&& m->data[i + block_x][j + block_y]>0)
			{
				return false;
			}
		}
	}
	return true;
}