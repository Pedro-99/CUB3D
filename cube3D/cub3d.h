#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include "/usr/local/include/mlx.h"

# define UP		126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
#define mapWidth 600
#define mapHeight 600
# define MAP_ROWS 24
# define MAP_COLS 24
#define WIDTH 1920
#define HEIGHT 1080

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			end;
	int			len;
	int			rows;
	int			cols;
	int			color;
	int			p_x;
	int			p_y;
	float			p_angle;
	int			world_map[mapWidth][mapHeight];
}		t_mlx;


int	render(t_mlx *mlx);
void	draw_pixel(t_mlx *mlx, int x, int y, int color);
int	get_color(int worldMap[mapWidth][mapHeight], int i, int j);
void 	cube(t_mlx *mlx, int x, int y, int color, int type);
void	initialize_world_map(t_mlx *mlx);
//void	mlx_get_screen_size(void *mlx_ptr, int *width, int *height);

#endif 
