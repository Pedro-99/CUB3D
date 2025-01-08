#include "cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_mlx	mlx;
	void	*mlx_;
	void	*win;
	void	*img;

	mlx_ = mlx_init();
	if (!mlx_)
		return (dprintf(2, "mlx_init failed\n"), 1);
	
	win = mlx_new_window(mlx_, WIDTH, HEIGHT, "CUBE3D");
	img = mlx_new_image(mlx_, WIDTH, HEIGHT);
	mlx.mlx = mlx_;
	mlx.img = img;
	mlx.win = win;
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.len, &mlx.end);
	initialize_world_map(&mlx);
	mlx.color = 0xffffff;
	mlx.p_x = 370;
	mlx.p_y = 130;
	mlx.p_angle = 50;
	//mlx_key_hook(mlx.win, key, &mlx);
	mlx_loop_hook(mlx.mlx, render, &mlx);
//	mlx_put_image_to_window(mlx_, win, img, 0, 0);
	mlx_loop(mlx_);

	return (0);
}
