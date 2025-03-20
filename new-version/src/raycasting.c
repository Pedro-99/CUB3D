#include "cub3d.h"

double	cast_ray(t_data *data, double ray_angle, int *side, double *wall_x)
{
	double ray_x = data->player.x;
	double ray_y = data->player.y;
	double dx = cos(ray_angle);
	double dy = sin(ray_angle);
	int hit = 0;
	double perp_wall_dist;

	int map_x = (int)(ray_x / TILE_UNIT);
	int map_y = (int)(ray_y / TILE_UNIT);

	int step_x;
	int step_y;

	if (dx > 0)
		step_x = 1;
	else
		step_x = -1;
	if (dy > 0)
		step_y = 1;
	else
		step_y = -1;

	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	if (dx > 0)
		side_dist_x = ((map_x + 1) * TILE_UNIT - ray_x) / dx;
	else
		side_dist_x = (ray_x - map_x * TILE_UNIT) / -dx;
	if (dy > 0)
		side_dist_y = ((map_y + 1) * TILE_UNIT - ray_y) / dy;
	else
		side_dist_y = (ray_y - map_y * TILE_UNIT) / -dy;

	if (dx == 0)
		delta_dist_x = 1e30;
	else
		delta_dist_x = fabs(TILE_UNIT / dx);
	if (dy == 0)
		delta_dist_y = 1e30;
	else
		delta_dist_y = fabs(TILE_UNIT / dy);

	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			*side = 0; // vertical
		} else {
			side_dist_y += delta_dist_y;
			map_y += step_y;
			*side = 1; // horizontal
		}

		if (map_x < 0 || map_x >= data->config.map_width || map_y < 0 || map_y >= data->config.map_height)
			break;

		if (data->config.map[map_y][map_x] == '1')
		{
			hit = 1;
		}
	}

	if (hit)
	{
		if (*side == 0)
		{
			perp_wall_dist = (side_dist_x - delta_dist_x);
			*wall_x = ray_y + perp_wall_dist * dy;
		}
		else
		{
			perp_wall_dist = (side_dist_y - delta_dist_y);
			*wall_x = ray_x + perp_wall_dist * dx;
		}
		*wall_x = fmod(*wall_x, TILE_UNIT) / TILE_UNIT; // to keep wallx between 0-1
		perp_wall_dist *= cos(ray_angle - data->player.angle); // correct fesheye effect
	}
	else
	{
		perp_wall_dist = data->config.height;
		*side = -1;
		*wall_x = 0;
	}

	return perp_wall_dist;
}