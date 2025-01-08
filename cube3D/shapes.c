#include "cub3d.h"

# define B_KEY		11
# define F_KEY		3
# define UP		126


void	line(void)
{
	return ;
}

void cube(t_mlx *mlx, int x, int y, int color, int type)
{
	(void)type;

    int cube_size = mapWidth / 24;  // Fixed size for each cube

    for (int i = 1; i < cube_size; i++)
    {
        for (int j = 1; j < cube_size; j++)
            draw_pixel(mlx, x + i, y + j, color);
    }
}
