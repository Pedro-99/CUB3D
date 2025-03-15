#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

#define WIDTH 800
#define HEIGHT 600
#define FOV 60
#define TILE_SIZE 64

typedef struct s_player {
	double x;
	double y;
	double angle; // In radians
} t_player;

typedef struct s_config {
	int width;
	int height;
	char *no_texture; // North texture path
	char *so_texture; // South texture path
	char *we_texture; // West texture path
	char *ea_texture; // East texture path
	uint32_t floor_color; // RGBA packed as 0xRRGGBBFF
	uint32_t ceil_color;  // RGBA packed as 0xRRGGBBFF
	char **map; // 2D map array
	int map_width;
	int map_height;
} t_config;

typedef struct s_data {
	mlx_t *mlx;
	mlx_image_t *img;
	t_player player;
	t_config config;
	mlx_texture_t *no_tex; // North texture
	mlx_texture_t *so_tex; // South texture
	mlx_texture_t *we_tex; // West texture
	mlx_texture_t *ea_tex; // East texture
} t_data;

void    ft_render(void *param);
void    ft_hook(void *param);
double  cast_ray(t_data *data, double ray_angle, int *side, double *wall_x);
void    parse_cub_file(const char *filename, t_data *data);
void    ft_error(const char *str);
void    load_textures(t_data *data);
void    free_textures(t_data *data);
double	to_radian(int value);
void    draw_ceil_and_floor(t_data *data);

#endif