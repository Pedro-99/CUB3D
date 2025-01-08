#include "cub3d.h"
#include <CoreGraphics/CGDisplayConfiguration.h>

int	get_color(int worldMap[mapWidth][mapHeight], int i, int j)
{
	if (worldMap[i][j] >= 1 && worldMap[i][j] <= 4)
		return (0x0000ff);
	else if (worldMap[i][j] == 0)
		return (0xffffff);
	return (0xffffff);
}


void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*add;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		add = mlx->addr + (y * mlx->len + x * (mlx->bpp / 8));
		*(unsigned int *)add = color;
	}
}



void get_screen_size(int *width, int *height)
{
    *width = CGDisplayPixelsWide(CGMainDisplayID());
    *height = CGDisplayPixelsHigh(CGMainDisplayID());
}

