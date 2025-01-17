#include "cub3d.h"

int	get_color(t_data *data, int i, int j)
{
	if (data->world_map[i][j] >= 1 && data->world_map[i][j] <= 4)
		return (0x0000ff);
	else if (data->world_map[i][j] == 0)
		return (0xffffff);
	return (0xffffff);
}


void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*add;

	if (x >= 0 && x < mlx->window_width && y >= 0 && y < mlx->window_height)
	{
		add = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
		*(unsigned int *)add = color;
	}
}

