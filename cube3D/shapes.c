#include "cub3d.h"

# define B_KEY		11
# define F_KEY		3

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

// void	circle(t_mlx *mlx)
// {
// 	int	x;
// 	int	y;

// 	x = -mlx->player->radius; 
// 	while (x <= mlx->player->radius)
// 	{
// 		y = -mlx->player->radius;
// 		while (y <= mlx->player->radius)
// 		{
// 			if (x * x + y * y <= mlx->player->radius * mlx->player->radius)
// 				draw_pixel(mlx, mlx->player->x + x , mlx->player->y + y, 0x00ff00);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void	line(t_mlx * mlx)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	x = 0;
// 	while (x <= mlx->player->radius * 10)
// 	{

// 		while (y <= mlx->player->radius * 10)
// 		{
// 			draw_pixel(mlx, mlx->player->x + x , mlx->player->y + y, 0x00ff00);
// 			y++;
// 		}
// 		x++;
// 	}
// }


void circle(t_mlx *mlx)
{
    int x, y;

    for (x = -mlx->player->radius; x <= mlx->player->radius; x++)
    {
        for (y = -mlx->player->radius; y <= mlx->player->radius; y++)
        {
            if (x * x + y * y <= mlx->player->radius * mlx->player->radius)
                draw_pixel(mlx, mlx->player->x + x, mlx->player->y + y, 0x00ff00);
        }
    }
}

// void line(t_mlx *mlx)
// {
//     int x;

//     for (x = 0; x <= 100; x++)
//     {
//         int y = tan(mlx->player->rotation_angle) * x;
//         draw_pixel(mlx, mlx->player->x + x, mlx->player->y + y, 0x00ff00);
//     }
// }
void line(t_mlx *mlx)
{
    int x, y;
    float line_length = 100.0; // Length of the line
    float angle = mlx->player->rotation_angle;

    for (int i = 0; i < line_length; i++)
    {
        x = mlx->player->x + cos(angle) * i;
        y = mlx->player->y + sin(angle) * i;
        draw_pixel(mlx, x, y, 0xff0000); // Draw line in red
    }
}

