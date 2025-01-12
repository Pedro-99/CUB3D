#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include "/usr/local/include/mlx.h"

# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define ESC		53
#define mapWidth 600
#define mapHeight 600
// # define MAP_ROWS 24
// # define MAP_COLS 24
# define WIDTH 600
# define HEIGHT 400
// #define WIDTH 1920
// #define HEIGHT 1080

// # define MAP_ROWS 15
// # define MAP_COLS 40

# define MAP_ROWS 20
# define MAP_COLS 30
# define CUBE_SIZE mapWidth / MAP_COLS

# define PI 3.14159265358979323846

typedef struct s_player
{
	int	x;
	int	y;
	int	radius;
	int	turn_direction;
	int	walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
}	t_player;

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
	int			cube_size;
	t_player		*player;
	int			world_map[MAP_ROWS][MAP_COLS];
}		t_mlx;


int		render(t_mlx *mlx);
void	draw_pixel(t_mlx *mlx, int x, int y, int color);
int		get_color(int worldMap[mapWidth][mapHeight], int i, int j);
void 	cube(t_mlx *mlx, int x, int y, int color, int type);
void	initialize_world_map(t_mlx *mlx);
//void	mlx_get_screen_size(void *mlx_ptr, int *width, int *height);
void	create_player(t_mlx *mlx);
void	circle(t_mlx *mlx);
int		event_handler(int key, t_mlx *mlx);
void	line(t_mlx * mlx);
void	player_movement(t_mlx *player);
int		key_release_handler(int key, t_mlx *mlx);
int		key_press_handler(int key, t_mlx *mlx);
void	process_movement(t_mlx *mlx);

#endif 
