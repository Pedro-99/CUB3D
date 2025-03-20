#include "cub3d.h"

void ft_error(const char *str)
{
	printf("Error: %s\n", str);
	fprintf(stderr, "%s\n", mlx_strerror(mlx_errno));
	exit(1);
}

void load_textures(t_data *data)
{
	data->no_tex = mlx_load_png(data->config.no_texture);
	data->so_tex = mlx_load_png(data->config.so_texture);
	data->we_tex = mlx_load_png(data->config.we_texture);
	data->ea_tex = mlx_load_png(data->config.ea_texture);

	if (!data->no_tex)
		ft_error("Failed to load north texture");
	if (!data->so_tex)
		ft_error("Failed to load south texture");
	if (!data->we_tex)
		ft_error("Failed to load west texture");
	if (!data->ea_tex)
		ft_error("Failed to load east texture");
}

void free_textures(t_data *data)
{
	if (data->no_tex) mlx_delete_texture(data->no_tex);
	if (data->so_tex) mlx_delete_texture(data->so_tex);
	if (data->we_tex) mlx_delete_texture(data->we_tex);
	if (data->ea_tex) mlx_delete_texture(data->ea_tex);
}

double	to_radian(int value)
{
	return (value  * M_PI / 180.0);
}