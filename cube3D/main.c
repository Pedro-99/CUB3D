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
	create_player(&mlx);
	mlx.color = 0xffffff;
	mlx.p_x = 370;
	mlx.p_y = 130;
	mlx.p_angle = 50;
	mlx_hook(mlx.win, 2, 1L << 0, key_press_handler, &mlx);   // Key press
	mlx_hook(mlx.win, 3, 1L << 1, key_release_handler, &mlx); // Key release

	//mlx_key_hook(mlx.win, event_handler, &mlx);

	mlx_loop_hook(mlx.mlx, render, &mlx);
//	mlx_put_image_to_window(mlx_, win, img, 0, 0);
	mlx_loop(mlx_);

	return (0);
}
