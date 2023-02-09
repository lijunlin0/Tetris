#include"block.h"
#include"game_map.h"

block::block(int value,game_map*map)
{
	m_value = value;
	m=map;
}
//能否左移
bool block::can_move_left()
{
	for (int i = 0; i < block::width; i++)
	{
		for (int j = 0; j < block::height; j++)
		{
			if (data[i][j] ==m_value)
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
			if (data[i][j] == m_value)
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
			if (data[i][j] == m_value)
			{
				//下方为边界
				if ((block_x + j + 1) > (game_map::HEIGHT-1))
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
	else if (x == 2 && y == 1) { return std::pair<int, int>(2, 2); }
	else if (x == 0 && y == 2) { return std::pair<int, int>(0, 1); }
	else if (x == 1 && y == 2) { return std::pair<int, int>(0, 2); }
	else if (x == 2 && y == 2) { return std::pair<int, int>(1, 2); }
}

//能否旋转
bool block::can_rotate()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			x = get_rotate_position(i, j).first;
			y = get_rotate_position(i, j).second;
			if (i == 1 && j == 1)
			{
				continue;
			}
			if (data[x][y] == m_value)
			{
				return false;
			}
			else if (data[get_obstacle_position(i, j).first][get_obstacle_position(i, j).second] == m_value)
			{
				return false;
			}
		}
	}
	return true;
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

//旋转
void block::rotate()
{
	int temp[block::width][block::height];
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			temp[i][j] = data[i][j];
		}
	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			data[get_rotate_position(i, j).first][get_rotate_position(i, j).second] = temp[i][j];
		}
	}
}
void block::reset()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (data[i][j] == m_value)
			{
				m->set_value(i + block_x, j + block_y, 0);
			}
		}
	}
}