#include "cub3d.h"




int render(t_mlx *mlx)
{
	int	i;
	int	j;
	int	centerX;
	int	centerY;
	int	mutable_coordinateX;
	int	mutable_coordinateY;
    // Clear screen
	int	cube_size; // Size of each "tile" on the map

	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		while (j < HEIGHT)
		{
            		draw_pixel(mlx, i, j, 0x000000);
			j++;
		}
		i++;
	}
    // Draw empty white map
    	centerX = (WIDTH / 2) - (mapWidth/ 2);
    	centerY = (HEIGHT / 2) - (mapHeight / 2);
    	i = 0;
	while (i < mapWidth)
	{
    		j = 0;
		while (j < mapHeight)
		{
            		draw_pixel(mlx, centerX + i, centerY + j, 0xffffff);
			j++;
		}
		i++;
	}
    // Draw walls
	i = 0;
	cube_size = mapWidth / 24;
	while (i < MAP_ROWS)
	{
		j = 0;
		while (j < MAP_COLS)
		{
			if (mlx->world_map[i][j] != 0)
			{
				mutable_coordinateX =  centerX + (cube_size * j);
				mutable_coordinateY =  centerY + (cube_size * i);
				cube(mlx, mutable_coordinateX, mutable_coordinateY, 0xff0000, 1);
			}
			j++;
		}
		i++;
	}


    // Display the image
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

    return (0);
}

