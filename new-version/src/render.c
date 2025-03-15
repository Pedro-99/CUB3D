#include "cub3d.h"

void ft_render(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	data = (t_data *)param;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * sizeof(uint32_t));

	double fov = to_radian(FOV);
	double ray_angle_increment = fov / data->config.width;

	draw_ceil_and_floor(data);
	x = 0;
	while (x < data->config.width)
	{
		double ray_angle = data->player.angle - (fov / 2) + (x * ray_angle_increment);
		int side;
		double wall_x;
		double wall_dist = cast_ray(data, ray_angle, &side, &wall_x);

		if (side == -1)
			continue;

		double wall_height = (data->config.height * TILE_SIZE) / wall_dist;
		if (wall_height > data->config.height)
			wall_height = data->config.height;

		int start_y = (data->config.height - (int)wall_height) / 2;
		int end_y = start_y + (int)wall_height;

		mlx_texture_t *texture;
		double ray_dir_x = cos(ray_angle);
		double ray_dir_y = sin(ray_angle);
		if (side == 0) {
			texture = (ray_dir_x > 0) ? data->ea_tex : data->we_tex;
		} else {
			texture = (ray_dir_y > 0) ? data->so_tex : data->no_tex;
		}

		if (!texture)
			continue;

		int tex_x = (int)(wall_x * texture->width);
		if ((side == 0 && ray_dir_x < 0) || (side == 1 && ray_dir_y > 0))
			tex_x = texture->width - tex_x - 1;

		y = start_y;
		while (y < end_y)
		{
			if (y >= 0 && y < data->config.height)
			{
				int tex_y = (int)(((y - start_y) * texture->height) / wall_height);
				uint32_t color = ((uint32_t *)texture->pixels)[tex_y * texture->width + tex_x];
				mlx_put_pixel(data->img, x, y, color);
			}
			y++;
		}
		x++;
	}
}