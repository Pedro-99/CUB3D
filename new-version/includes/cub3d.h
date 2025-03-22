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
#define TILE_UNIT 64

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_list
{
	char		*str;
	struct s_list	*next;
}	t_list;

typedef struct s_config
{
	int		width;
	int		height;
	char		*no_texture;
	int		flag_player;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	uint32_t	floor_color;
	uint32_t	ceil_color;
	char		**map;
	int		map_width;
	int		map_height;
}	t_config;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_config	config;
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*we_tex;
	mlx_texture_t	*ea_tex;
}	t_data;

typedef struct s_ray_step
{
	int	step_x;
	int	step_y;
	double	side_dist_x;
	double	side_dist_y;
}	t_ray_step;

typedef struct s_ray
{
	double	angle;
	double	dx;
	double	dy;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_x;
	int	side;
	double	dist;
	int	hit;
}	t_ray;

t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_render(void *param);
void	ft_hook(void *param);
double	cast_ray(t_data *data, t_ray *ray);
void	parse_cub_file(const char *filename, t_data *data);
void	ft_error(const char *str);
void	load_textures(t_data *data);
void	free_textures(t_data *data);
double	to_radian(int value);
void	draw_ceil_and_floor(t_data *data);
void	move_forward(t_data *data, double move_speed);
void	move_backward(t_data *data, double move_speed);
void	turn_right(t_data *data, double rot_speed);
void	turn_left(t_data *data, double rot_speed);
char	*ft_strdup1(const char *s1, int len);
void	move_right(t_data *data, double move_speed);
void	move_left(t_data *data, double move_speed);

#endif