#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <sys/time.h>
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
// #define WIDTH 1920
// #define HEIGHT 1080

// # define MAP_ROWS 15
// # define MAP_COLS 40

# define CUBE_SIZE 50
# define MAP_ROWS 30
# define MAP_COLS 20
# define WIDTH CUBE_SIZE * MAP_ROWS
# define HEIGHT CUBE_SIZE * MAP_COLS


# define FOV_ANGLE (60 * (PI / 180))  // Convert degrees to radians
# define WALL_STRIP_WIDTH 1            // Width of each wall strip
# define NUM_RAYS  (WIDTH / WALL_STRIP_WIDTH) // Number of rays based on screen width


# define PI 3.14159265358979323846

typedef void (*renderfunc)(void *);
typedef void (*cast)(void *);

typedef struct s_ray
{
	float	ray_angle;
    int		hit_wall_x_at;
    int		hit_wall_y_at;
    int		distance;
    int		is_vertical_hit_found;
	renderfunc	render;
}	t_ray;

typedef struct s_player
{
	int		x;
	int		y;
	int		radius;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	t_ray	*rays;
	renderfunc	render;
	cast		cast_rays;
}	t_player;

typedef struct s_mlx
{
	int			window_width;
	int			window_height;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			end;
	int			len;
	int			color;
	int			cube_size;
	t_player	*player;
	int			world_map[MAP_ROWS][MAP_COLS];
	renderfunc	render;
}		t_mlx;

typedef struct s_data
{
	int			world_map[MAP_COLS][MAP_ROWS];
	t_mlx		*mlx;
	t_player	*player;
	int			frames;
	size_t	start_time;
}	t_data;


size_t	get_current_time(void);
int	is_collision_found(t_data *data, int x, int y);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int		render(t_data *data);
void	draw_pixel(t_mlx *mlx, int x, int y, int color);
int	get_color(t_data *data, int i, int j);
void 	cube(t_mlx *mlx, int x, int y, int color, int type);
void 	initialize_world_map(t_data *data);
//void	mlx_get_screen_size(void *mlx_ptr, int *width, int *height);
void	create_player(t_mlx *mlx);
void	circle(t_data *data);
int		event_handler(int key, t_mlx *mlx);
void	line(t_mlx * mlx, int *ray_id);
void	player_movement(t_data *data);
int		key_release_handler(int key, t_mlx *mlx);
int		key_press_handler(int key, t_mlx *mlx);
void	process_movement(t_data *data);
void    init_rays(t_data *game);
double	distanceBetweenPoints(int x1, int y1, int x2, int y2);
void	render_player(void *data);
void	render_ray(void *data);
void	render_map(void *data);
void	init_player(t_data *data);
void    init_data(t_data *data, t_mlx *mlx);
void	DDA(t_mlx *mlx, int X0, int Y0, int X1, int Y1);


#endif 
