#include "cub3d.h"

void ft_hook(void *param)
{
	t_data *data = (t_data *)param;
	double move_speed = 5.0;
	double rot_speed = 0.1;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward(data, move_speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S)) {
		move_backward(data, move_speed);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		turn_left(data, rot_speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		turn_right(data, rot_speed);
}
