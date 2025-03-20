#include "cub3d.h"

void ft_render(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	data = (t_data *)param;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * sizeof(int));

	double fov = to_radian(FOV);
	double ray_angle_increment = fov / data->config.width; // distance between two rays 

	draw_ceil_and_floor(data);
	x = 0;
	while (x < data->config.width)
	{
		double	ray_angle = data->player.angle - (fov / 2) + (x * ray_angle_increment); // the most left ray 
		int 	side; // wash l horizontal wla l vertical
		double 	wall_x; // fin bedqqbt dreb f l7ayt
		double 	wall_dist = cast_ray(data, ray_angle, &side, &wall_x);

		if (side == -1)
			continue;

		double wall_height = (data->config.height * TILE_UNIT) / wall_dist;
		// if wall-HEIGHT > window HEIGHT
			// wall-height = comfig height
		int start_y = (data->config.height - (int)wall_height) / 2; // centri l mlawi (hakak charit or strip height)
		// start_y = start_y % data->config.height; // dqrha rez9i
		int end_y = start_y + (int)wall_height;

		mlx_texture_t *texture;
		double ray_dir_x = cos(ray_angle);
		double ray_dir_y = sin(ray_angle);
		if (side == 0) {
			if (ray_dir_x > 0)
				texture = data->ea_tex;
			else
				texture = data->we_tex;
		} else {
			if (ray_dir_y > 0)
				texture = data->so_tex;
			else
				texture = data->no_tex;
		}

		if (!texture)
			continue;

		int tex_x = (int)(wall_x * texture->width); // texture width 512px 
		if ((side == 0 && ray_dir_x < 0) || (side == 1 && ray_dir_y > 0))
			tex_x = texture->width - tex_x - 1; // suppose tex-x is 1 then tex-x is 512 - 512 -1 = -1

		y = start_y;
		while (y < end_y)
		{
			if (y >= 0 && y < data->config.height)
			{
				int tex_y = (int)(((y - start_y) * texture->height) / wall_height);
				int color = ((int *)texture->pixels)[tex_y * texture->width + tex_x];
				mlx_put_pixel(data->img, x, y, color);
			}
			y++;
		}
		x++;
	}
}