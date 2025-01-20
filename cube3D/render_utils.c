#include "cub3d.h"


void cast_ray(void *data, t_ray *ray, int ray_id)
{
    double xintercept, yintercept;
    double xstep, ystep;
    t_data *game;

    game = (t_data *)data;

    // HORIZONTAL RAY-GRID INTERSECTION
    int foundHorzWallHit = 0;
    double horzWallHitX = 0;
    double horzWallHitY = 0;


    double ray_angle = game->player->rotation_angle - (FOV_ANGLE / 2) + 
                      (ray_id * FOV_ANGLE / NUM_RAYS);
    
    // Normalize the angle
    ray->ray_angle = normalizedAngle(ray_angle);

    // Calculate intercepts
    if (sin(ray->ray_angle) > 0) {
        yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
    } else {
        yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE;
    }
    xintercept = game->player->x + (yintercept - game->player->y) / tan(ray->ray_angle);

    ystep = (sin(ray->ray_angle) > 0) ? CUBE_SIZE : -CUBE_SIZE;
    xstep = ystep / tan(ray->ray_angle);

    double nextHorzTouchX = xintercept;
    double nextHorzTouchY = yintercept;

    // Loop through grid
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= game->mlx->window_width
			&& nextHorzTouchY >= 0 && nextHorzTouchY <= game->mlx->window_height) {
        if (is_collision_found(game, (int)nextHorzTouchX, (int)(nextHorzTouchY - (ystep < 0 ? 1 : 0)))) {
            foundHorzWallHit = 1;
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            break;
        } else {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    // Update ray properties
    if (foundHorzWallHit) {
        ray->hit_wall_x_at = horzWallHitX;
        ray->hit_wall_y_at = horzWallHitY;
        ray->distance = distanceBetweenPoints(game->player->x, game->player->y, ray->hit_wall_x_at, ray->hit_wall_y_at);
    } else {
        ray->hit_wall_x_at = 0;
        ray->hit_wall_y_at = 0;
        ray->distance = INT_MAX;
    }
}


void	cast_all_rays(void *data)
{
	t_data	*game;
	int		i;
	
	game = (t_data *)data;
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(game, &game->player->rays[i], i);
		i++;
	}

}

void	render_player(void *data)
{
	t_data	*game;
	int		i;
	game = (t_data *)data;

	circle(game);
	i = 0;
	cast_all_rays(game);
	// render the rays
	while (i < NUM_RAYS)
	{
		// ray
		DDA(game, game->player->x, game->player->y, game->player->rays[i].hit_wall_x_at, game->player->rays[i].hit_wall_y_at);
		i++;
	}
}

void	clean_map(t_data *game)
{
	int j;
	int i = 0;

	i = 0;
	while (i < game->mlx->window_width)
	{
    	j = 0;
		while (j < game->mlx->window_height)
		{
            draw_pixel(game->mlx, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void    map_playground(t_data *game)
{
	int j;
	int i = 0;

	process_movement(game);
	clean_map(game);
	i = 0;
	while (i < MAP_COLS)
	{
		j = 0;
		while (j < MAP_ROWS)
		{
			int mutable_coordinateX = CUBE_SIZE * j;
			int mutable_coordinateY = CUBE_SIZE * i;

			if (game->world_map[i][j] != 0)
				cube(game->mlx, mutable_coordinateX, mutable_coordinateY, 0xff0000, 1);
			else
				cube(game->mlx, mutable_coordinateX, mutable_coordinateY, 0xffffff, 1);
			j++;
		}
		i++;
	}
	game->player->render(game);
}

void	render_map(void *data)
{
	t_data *game = (t_data *)data;
	
	if (!game->mlx || !game->mlx->mlx || !game->mlx->win)
		return;
	map_playground(game);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->mlx->img, 0, 0);
}