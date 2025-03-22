#include "cub3d.h"

static mlx_texture_t	*get_wall_texture(t_data *data, t_ray ray)
{
	double	ray_dir_x;
	double	ray_dir_y;

	ray_dir_x = cos(ray.angle);
	ray_dir_y = sin(ray.angle);
	if (ray.side == 0)
	{
		if (ray_dir_x > 0)
			return (data->ea_tex);
		return (data->we_tex);
	}
	else
	{
		if (ray_dir_y > 0)
			return (data->so_tex);
		return (data->no_tex);
	}
}

static void	draw_wall_column(t_data *data, t_ray ray, int x, double wall_height)
{
	int				start_y;
	int				end_y;
	mlx_texture_t	*texture;
	int				y;

	start_y = (data->config.height - (int)wall_height) / 2;
	end_y = start_y + (int)wall_height;
	texture = get_wall_texture(data, ray);
	if (!texture)
		return ;
	y = start_y;
	while (y < end_y)
	{
		if (y >= 0 && y < data->config.height)
		{
			int	tex_x = (int)(ray.wall_x * texture->width);
			int	tex_y = (int)(((y - start_y) * texture->height) / wall_height);
			if ((ray.side == 0 && ray.dx < 0) || (ray.side == 1 && ray.dy > 0))
				tex_x = texture->width - tex_x - 1;
			mlx_put_pixel(data->img, x, y, ((int *)texture->pixels)[tex_y * texture->width + tex_x]);
		}
		y++;
	}
}

static void	projection_3d(t_data *data, double fov, double ray_angle_increment)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < data->config.width)
	{
		ray.angle = data->player.angle - (fov / 2) + (x * ray_angle_increment);
		ray.dist = cast_ray(data, &ray);
		if (ray.side != -1)
		{
			double	wall_height;

			wall_height = (data->config.height * TILE_UNIT) / ray.dist;
			draw_wall_column(data, ray, x, wall_height);
		}
		x++;
	}
}

void	ft_render(void *param)
{
	t_data	*data;
	double	fov;

	data = (t_data *)param;
	ft_memset(data->img->pixels, 0, data->img->width * data->img->height * sizeof(int));
	fov = to_radian(FOV);
	draw_ceil_and_floor(data);
	projection_3d(data, fov, fov / data->config.width);
}