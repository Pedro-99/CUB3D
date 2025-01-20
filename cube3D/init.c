#include "cub3d.h"

void initialize_world_map(t_data *data)
{

int world_map[MAP_COLS][MAP_ROWS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,2,0,0,0,0,0,3,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,3,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,2,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,1},
    {1,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


    for (int i = 0; i < MAP_COLS; i++) {
        for (int j = 0; j < MAP_ROWS; j++) {
		data->world_map[i][j] = world_map[i][j];
        }
    }
}


void	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		printf ("malloc failed - player allocation\n");
		return ;
	}
    // set_player_position(mlx);

    data->player->x = data->mlx->window_width / 2;
    data->player->y = data->mlx->window_width / 2;
	data->player->radius = 3;
	data->player->turn_direction = 0;
	data->player->walk_direction = 0;
	data->player->rotation_angle = PI / 2;
	data->player->move_speed= 2.0;
	data->player->rotation_speed = 2 * (PI / 180);
    data->player->render = render_player;
}

float normalizedAngle(float angle)
{
    float normalized = fmod(angle, 2 * M_PI); // Use fmod for floating-point modulus
    if (normalized < 0) {
        normalized += 2 * M_PI; // Ensure the angle is positive
    }
    return normalized;
}

// float normalizedAngle(float angle) {
//     while (angle < 0) angle += 2 * PI;
//     while (angle >= 2 * PI) angle -= 2 * PI;
//     return angle;
// }


void    init_rays(t_data *game)
{
    t_ray   *rays = malloc(sizeof(t_ray) * NUM_RAYS);
    float	ray_angle;
    int i;

    i = 0;
    ray_angle = game->player->rotation_angle - (FOV_ANGLE / 2);
    while (i < NUM_RAYS)
    {
        rays[i].hit_wall_x_at = 0;
        rays[i].hit_wall_y_at = 0;
        rays[i].distance = 0;
        rays[i].ray_angle = ray_angle;
        // rays[i].ray_angle = normalizedAngle(ray_angle);
        rays[i].is_vertical_hit_found = 0;
        ray_angle += FOV_ANGLE / NUM_RAYS;
        // rays[i].render = render_ray;
        i++;
    }
    game->player->rays = rays;
}

void    init_data(t_data *data, t_mlx *mlx)
{
    initialize_world_map(data);
    data->mlx = mlx;
    init_player(data);
    init_rays(data);
}