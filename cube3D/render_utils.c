#include "cub3d.h"

// void	cast_ray(void *data, t_ray *ray)
// {
//     int xintercept, yintercept;
//     int xstep, ystep;
// 	t_data *game;

// 	game = (t_data *)data;

//     // HORIZONTAL RAY-GRID INTERSECTION
//     int foundHorzWallHit = 0;
//     int horzWallHitX = 0;
//     int horzWallHitY = 0;
	
//     if (sin((double)ray->ray_angle) > 0) {
//         yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
//     } else {
//         yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE;
//     }
//     xintercept = game->player->x + (yintercept - game->player->y) / tan((double)ray->ray_angle);

//     ystep = (sin((double)ray->ray_angle) > 0) ? CUBE_SIZE : -CUBE_SIZE;
//     xstep = ystep / tan((double)ray->ray_angle);

//     int nextHorzTouchX = xintercept;
//     int nextHorzTouchY = yintercept;

//     while (nextHorzTouchX >= 0 && nextHorzTouchX <= game->mlx->window_width && nextHorzTouchY >= 0 && nextHorzTouchY <= game->mlx->window_height) {
//         if (is_collision_found(game, nextHorzTouchX, nextHorzTouchY - (ystep < 0 ? 1 : 0))) {
//             foundHorzWallHit = 1;
//             horzWallHitX = nextHorzTouchX;
//             horzWallHitY = nextHorzTouchY;
//             break;
//         }
// 		else
// 		{
// 			nextHorzTouchX += xstep;
// 			nextHorzTouchY += ystep;
// 		}
//     }

// 	printf("before hitx : %d\thity : %d\n", ray->hit_wall_x_at, ray->hit_wall_y_at);
//     ray->hit_wall_x_at = horzWallHitX;
//     ray->hit_wall_y_at = horzWallHitY;
// 	printf("after hitx : %d\thity : %d\n", ray->hit_wall_x_at, ray->hit_wall_y_at);
// 	if (foundHorzWallHit)
// 		ray->distance = distanceBetweenPoints(game->player->x, game->player->y, ray->hit_wall_x_at, horzWallHitY);
// 	else
//     	ray->distance = INT_MAX;
// }

void cast_ray(void *data, t_ray *ray)
{
    double xintercept, yintercept;
    double xstep, ystep;
    t_data *game;

    game = (t_data *)data;

    // HORIZONTAL RAY-GRID INTERSECTION
    int foundHorzWallHit = 0;
    double horzWallHitX = 0;
    double horzWallHitY = 0;

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

// printf("%d\n");
    // Update ray properties
    if (foundHorzWallHit) {
        ray->hit_wall_x_at = (int)horzWallHitX;
        ray->hit_wall_y_at = (int)horzWallHitY;
        ray->distance = distanceBetweenPoints(game->player->x, game->player->y, horzWallHitX, horzWallHitY);
    } else {
        ray->hit_wall_x_at = 0;
        ray->hit_wall_y_at = 0;
        ray->distance = INT_MAX;
    }
}


// void cast_ray(void *data, t_ray *ray)
// {
//     t_data *game = (t_data *)data;
//     if (!game || !ray || !game->player) // Add null checks
//         return;

//     // Initialize variables with double precision
//     double xintercept, yintercept;
//     double xstep, ystep;
    
//     // HORIZONTAL RAY-GRID INTERSECTION
//     int foundHorzWallHit = 0;
//     double horzWallHitX = 0;
//     double horzWallHitY = 0;
    
//     // Calculate yintercept with proper type conversion
//     yintercept = floor(game->player->y / (double)CUBE_SIZE) * CUBE_SIZE;
//     if (sin(ray->ray_angle) > 0) {
//         yintercept += CUBE_SIZE;
//     }
    
//     // Calculate xintercept using proper floating-point arithmetic
//     xintercept = game->player->x + (yintercept - game->player->y) / tan(ray->ray_angle);

//     // Calculate steps using proper floating-point arithmetic
//     ystep = (sin(ray->ray_angle) > 0) ? CUBE_SIZE : -CUBE_SIZE;
//     xstep = CUBE_SIZE / tan(ray->ray_angle);
//     if ((cos(ray->ray_angle) < 0 && xstep > 0) || (cos(ray->ray_angle) > 0 && xstep < 0)) {
//         xstep = -xstep;
//     }

//     double nextHorzTouchX = xintercept;
//     double nextHorzTouchY = yintercept;

//     // Add boundary checks
//     while (nextHorzTouchX >= 0 && nextHorzTouchX <= game->mlx->window_width &&
//            nextHorzTouchY >= 0 && nextHorzTouchY <= game->mlx->window_height) {
        
//         int checkY = nextHorzTouchY - (ystep < 0 ? 1 : 0);
        
//         if (is_collision_found(game, (int)nextHorzTouchX, checkY)) {
//             foundHorzWallHit = 1;
//             horzWallHitX = nextHorzTouchX;
//             horzWallHitY = nextHorzTouchY;
//             break;
//         }
//         nextHorzTouchX += xstep;
//         nextHorzTouchY += ystep;
//     }

//     // Store results with proper type conversion
//     ray->hit_wall_x_at = (int)horzWallHitX;
//     ray->hit_wall_y_at = (int)horzWallHitY;
    
//     if (foundHorzWallHit) {
//         ray->distance = sqrt(pow(game->player->x - horzWallHitX, 2) + 
//                            pow(game->player->y - horzWallHitY, 2));
//     } else {
//         ray->distance = INT_MAX;
//     }
// }

void	cast_all_rays(void *data)
{
	t_data	*game;
	int		i;
	
	game = (t_data *)data;
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(game, &game->player->rays[i]);
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
	while (i < NUM_RAYS)
	{
		DDA(game->mlx, game->player->x, game->player->y, game->player->rays[i].hit_wall_x_at, game->player->rays[i].hit_wall_y_at);
		i++;
	}
}




// void cast_rays(t_data *data)
// {
// 	int	i;
// 	
//     // start first ray subtracting half of the FOV
//     float rayAngle = data->mlx->player->rotation_angle - (FOV_ANGLE / 2);

//     // loop all columns casting the rays
// 	i = 0;
//     while (data->mlx->player->rays[i])
// 	{
//         cast_ray(data->mlx, &data->mlx->player->rays[i]);
//         rayAngle += FOV_ANGLE / NUM_RAYS;
// 		i++;
//     }	
// }



// void	render_ray(void *data)
// {
// 	t_data	*game;
// 	int	i;

// 	game = (t_data *)data;
// 	i = 0;
// 	while (i < 10)
// 	{
// 		DDA(game->mlx, game->player->x, game->player->y, game->player->rays[i].hit_wall_x_at, game->player->rays[i].hit_wall_y_at);
// 		i++;
// 	}
// }

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