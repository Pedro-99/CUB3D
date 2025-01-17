#include "cub3d.h"


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday failed\n", 22);
	return (time.tv_sec + time.tv_usec / 1000000);
}

int	render_worldmap(t_data *data)
{
	data->frames++;
	if (get_current_time() - data->start_time >= 1)
	{
		printf("FPS\t=> %d\n", data->frames);
		data->frames = 0;
		data->start_time = get_current_time();
	}
	data->mlx->render(data);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_mlx	mlx;
	void	*mlx_connection;
	void	*win;
	void	*img;
	t_data	data;
	int		w_width;
	int		w_height;
	

	w_width = CUBE_SIZE * MAP_ROWS;
	w_height = CUBE_SIZE * MAP_COLS;
	mlx_connection = mlx_init();
	if (!mlx_connection)
		return (dprintf(2, "mlx_init failed\n"), 1);
	win = mlx_new_window(mlx_connection, w_width, w_height, "CUBE3D");
	img = mlx_new_image(mlx_connection, w_width, w_height);
	mlx.mlx = mlx_connection;
	mlx.img = img;
	mlx.win = win;
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.len, &mlx.end);
	mlx.color = 0xffffff;
	mlx.render = render_map;
	mlx.window_width = w_width;
	mlx.window_height = w_height;
	init_data(&data, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press_handler, &mlx);   // Key press
	mlx_hook(mlx.win, 3, 1L << 1, key_release_handler, &mlx); // Key release
//	mlx_key_hook(mlx.win, event_handler, &mlx);
	data.start_time = get_current_time();
	data.frames = 0;
	mlx_loop_hook(mlx.mlx, render_worldmap, &data);
	mlx_loop(mlx_connection);

	return (0);
}

