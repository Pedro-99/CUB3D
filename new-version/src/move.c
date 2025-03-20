#include "cub3d.h"

static  int check_collision(t_data *data, int map_x, int map_y)
{
    if (map_x >= 0 && map_x < data->config.map_width && 
		map_y >= 0 && map_y < data->config.map_height &&
		data->config.map[map_y][map_x] != '1')
            return (0);
    return (1);
}

void    move_forward(t_data *data, double move_speed)
{
	double new_x = data->player.x + cos(data->player.angle) * move_speed;
	double new_y = data->player.y + sin(data->player.angle) * move_speed;
	int map_x = (int)(new_x / TILE_UNIT);
	int map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void    move_right(t_data *data, double move_speed)
{
	double new_x = data->player.x + cos(data->player.angle + M_PI / 2) * move_speed;
	double new_y = data->player.y + sin(data->player.angle + M_PI / 2) * move_speed;
	int map_x = (int)(new_x / TILE_UNIT);
	int map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void    move_left(t_data *data, double move_speed)
{
	double new_x = data->player.x + cos(data->player.angle - M_PI / 2) * move_speed;
	double new_y = data->player.y + sin(data->player.angle - M_PI / 2) * move_speed;
	int map_x = (int)(new_x / TILE_UNIT);
	int map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
}

void    move_backward(t_data *data, double move_speed)
{
	double new_x = data->player.x - cos(data->player.angle) * move_speed;
	double new_y = data->player.y - sin(data->player.angle) * move_speed;
	int map_x = (int)(new_x / TILE_UNIT);
	int map_y = (int)(new_y / TILE_UNIT);
	if (!check_collision(data, map_x, map_y))
    {
		data->player.x = new_x;
		data->player.y = new_y;
	}
}


void    turn_right(t_data *data, double rot_speed)
{
	data->player.angle += rot_speed;
}

void    turn_left(t_data *data, double rot_speed)
{
	data->player.angle -= rot_speed;
}