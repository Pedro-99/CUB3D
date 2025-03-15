#include "cub3d.h"

double cast_ray(t_data *data, double ray_angle, int *side, double *wall_x)
{
	double ray_x = data->player.x;
	double ray_y = data->player.y;
	double dx = cos(ray_angle);
	double dy = sin(ray_angle);

	int map_x = (int)(ray_x / TILE_SIZE);
	int map_y = (int)(ray_y / TILE_SIZE);

	int step_x = (dx > 0) ? 1 : -1;
	int step_y = (dy > 0) ? 1 : -1;

	double side_dist_x = (dx > 0) ? ((map_x + 1) * TILE_SIZE - ray_x) / dx : (ray_x - map_x * TILE_SIZE) / -dx;
	double side_dist_y = (dy > 0) ? ((map_y + 1) * TILE_SIZE - ray_y) / dy : (ray_y - map_y * TILE_SIZE) / -dy;

	double delta_dist_x = (dx == 0) ? 1e30 : fabs(TILE_SIZE / dx);
	double delta_dist_y = (dy == 0) ? 1e30 : fabs(TILE_SIZE / dy);

	int hit = 0;
	double perp_wall_dist;

	while (!hit) {
		if (side_dist_x < side_dist_y) {
			side_dist_x += delta_dist_x;
			map_x += step_x;
			*side = 0;
		} else {
			side_dist_y += delta_dist_y;
			map_y += step_y;
			*side = 1;
		}

		if (map_x < 0 || map_x >= data->config.map_width || map_y < 0 || map_y >= data->config.map_height)
			break;

		if (data->config.map[map_y][map_x] == '1') {
			hit = 1;
		}
	}

	if (hit) {
		if (*side == 0) {
			perp_wall_dist = (side_dist_x - delta_dist_x);
			*wall_x = ray_y + perp_wall_dist * dy;
		} else {
			perp_wall_dist = (side_dist_y - delta_dist_y);
			*wall_x = ray_x + perp_wall_dist * dx;
		}
		*wall_x = fmod(*wall_x, TILE_SIZE) / TILE_SIZE;
		perp_wall_dist *= cos(ray_angle - data->player.angle);
	} else {
		perp_wall_dist = data->config.height;
		*side = -1;
		*wall_x = 0;
	}

	return perp_wall_dist;
}