#include "cub3d.h"

static void	init_ray(t_ray *ray, t_ray_step *step)
{
	ray->dx = cos(ray->angle);
	ray->dy = sin(ray->angle);
	ray->hit = 0;
	if (ray->dx > 0)
		step->step_x = 1;
	else
		step->step_x = -1;
	if (ray->dy > 0)
		step->step_y = 1;
	else
		step->step_y = -1;
	if (ray->dx == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(TILE_UNIT / ray->dx);
	if (ray->dy == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(TILE_UNIT / ray->dy);
}

static void	set_side_dist(t_data *data, t_ray *ray, t_ray_step *step)
{
	int		map_x;
	int		map_y;

	map_x = (int)(data->player.x / TILE_UNIT);
	map_y = (int)(data->player.y / TILE_UNIT);
	if (ray->dx > 0)
		step->side_dist_x = ((map_x + 1) * TILE_UNIT - data->player.x) / ray->dx;
	else
		step->side_dist_x = (data->player.x - map_x * TILE_UNIT) / -ray->dx;
	if (ray->dy > 0)
		step->side_dist_y = ((map_y + 1) * TILE_UNIT - data->player.y) / ray->dy;
	else
		step->side_dist_y = (data->player.y - map_y * TILE_UNIT) / -ray->dy;
}

static void	step_ray(t_data *data, t_ray *ray, t_ray_step *step)
{
	int		map_x;
	int		map_y;

	map_x = (int)(data->player.x / TILE_UNIT);
	map_y = (int)(data->player.y / TILE_UNIT);
	while (!ray->hit)
	{
		if (step->side_dist_x < step->side_dist_y)
		{
			step->side_dist_x += ray->delta_dist_x;
			map_x += step->step_x;
			ray->side = 0;
		}
		else
		{
			step->side_dist_y += ray->delta_dist_y;
			map_y += step->step_y;
			ray->side = 1;
		}
		if (map_x < 0 || map_x >= data->config.map_width || map_y < 0
			|| map_y >= data->config.map_height)
			break ;
		if (data->config.map[map_y][map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_dist(t_data *data, t_ray *ray, t_ray_step *step)
{
	double	ray_x;
	double	ray_y;

	ray_x = data->player.x;
	ray_y = data->player.y;
	if (ray->hit)
	{
		if (ray->side == 0)
		{
			ray->dist = step->side_dist_x - ray->delta_dist_x;
			ray->wall_x = ray_y + ray->dist * ray->dy;
		}
		else
		{
			ray->dist = step->side_dist_y - ray->delta_dist_y;
			ray->wall_x = ray_x + ray->dist * ray->dx;
		}
		ray->wall_x = fmod(ray->wall_x, TILE_UNIT) / TILE_UNIT;
		ray->dist *= cos(ray->angle - data->player.angle);
	}
	else
	{
		ray->dist = data->config.height;
		ray->side = -1;
		ray->wall_x = 0;
	}
}

double	cast_ray(t_data *data, t_ray *ray)
{
	t_ray_step	step;

	init_ray(ray, &step);
	set_side_dist(data, ray, &step);
	step_ray(data, ray, &step);
	calc_dist(data, ray, &step);
	return (ray->dist);
}