#include "cub3d.h"

void ft_hook(void *param)
{
    t_data *data = (t_data *)param;
    double move_speed = 5.0;
    double rot_speed = 0.1;

    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    if (mlx_is_key_down(data->mlx, MLX_KEY_W)) {
        double new_x = data->player.x + cos(data->player.angle) * move_speed;
        double new_y = data->player.y + sin(data->player.angle) * move_speed;
        int map_x = (int)(new_x / 64);
        int map_y = (int)(new_y / 64);
        printf("x: %d\ty: %d\tmap_x: %d\tmap_y: %d\n", (int)new_x, (int)new_y, map_x, map_y);
        if (map_x >= 0 && map_x < data->config.map_width && 
            map_y >= 0 && map_y < data->config.map_height &&
            data->config.map[map_y][map_x] != '1') {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S)) {
        double new_x = data->player.x - cos(data->player.angle) * move_speed;
        double new_y = data->player.y - sin(data->player.angle) * move_speed;
        int map_x = (int)(new_x / 64);
        int map_y = (int)(new_y / 64);
        printf("x: %d\ty: %d\tmap_x: %d\tmap_y: %d\n", (int)new_x, (int)new_y, map_x, map_y);
        if (map_x >= 0 && map_x < data->config.map_width && 
            map_y >= 0 && map_y < data->config.map_height &&
            data->config.map[map_y][map_x] != '1') {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->player.angle -= rot_speed;
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        data->player.angle += rot_speed;
}