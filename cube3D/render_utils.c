#include "cub3d.h"

// void	find_ray_grid_inter(void *data, t_ray *ray, int ray_id, t_ray_inter *ray_inter, Intersection type_to_find)
// {
//     t_data		*game;
// 	double		ray_angle;
// 	double 		nextInterTouchX;
// 	double 		nextInterTouchY;

//     game = (t_data *)data;
// 	ray_angle = game->player->rotation_angle - (FOV_ANGLE / 2) + 
//                       (ray_id * FOV_ANGLE / NUM_RAYS);
//     // Normalize the angle
//     ray->ray_angle = normalizedAngle(ray_angle);

// 	if (type_to_find == HORIZONTAL)
// 	{
// 		// Calculate intercepts
// 		if (sin(ray->ray_angle) > 0)
// 		{
// 			ray_inter->yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
// 		} else {
// 			ray_inter->yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE;
// 		}
// 		ray_inter->xintercept = game->player->x + (ray_inter->yintercept - game->player->y) / tan(ray->ray_angle);
// 		ray_inter->ystep = (sin(ray->ray_angle) > 0) ? CUBE_SIZE : -CUBE_SIZE;
// 		ray_inter->xstep = ray_inter->ystep / tan(ray->ray_angle);
// 		nextInterTouchX = ray_inter->xintercept;
// 		nextInterTouchY = ray_inter->yintercept;
// 		// Loop through grid
// 		while (nextInterTouchX >= 0 && nextInterTouchX <= game->mlx->window_width
// 				&& nextInterTouchY >= 0 && nextInterTouchY <= game->mlx->window_height)
// 		{
// 			if (is_collision_found(game, (int)nextInterTouchX, (int)(nextInterTouchY - (ray_inter->ystep < 0 ? 1 : 0)))) {
// 				ray_inter->wall_inter_type = HORIZONTAL;
// 				ray_inter->hori_inter_wall_hit_x_at = nextInterTouchX;
// 				ray_inter->hori_inter_wall_hit_y_at = nextInterTouchY;
// 				break;
// 			} else {
// 				nextInterTouchX += ray_inter->xstep;
// 				nextInterTouchY += ray_inter->ystep;
// 			}
// 		}
// 	}
// 	else if (type_to_find == VERTICAL)
// 	{
// 		// Calculate intercepts
// 		if (sin(ray->ray_angle) > 0)
// 		{
// 			ray_inter->xintercept = floor(game->player->x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
// 		} else {
// 			ray_inter->xintercept = floor(game->player->x / CUBE_SIZE) * CUBE_SIZE;
// 		}
// 		ray_inter->yintercept = game->player->y + (ray_inter->xintercept - game->player->x) / tan(ray->ray_angle);
// 		ray_inter->xstep = (sin(ray->ray_angle) > 0) ? CUBE_SIZE : -CUBE_SIZE;
// 		ray_inter->ystep = ray_inter->xstep / tan(ray->ray_angle);
// 		nextInterTouchX = ray_inter->xintercept;
// 		nextInterTouchY = ray_inter->yintercept;

// 		// Loop through grid
// 		while (nextInterTouchX >= 0 && nextInterTouchX <= game->mlx->window_width
// 				&& nextInterTouchY >= 0 && nextInterTouchY <= game->mlx->window_height)
// 		{
// 			if (is_collision_found(game, (int)nextInterTouchX, (int)(nextInterTouchY - (ray_inter->ystep < 0 ? 1 : 0)))) {
// 				ray_inter->wall_inter_type = VERTICAL;
// 				ray_inter->vert_inter_wall_hit_x_at = nextInterTouchX;
// 				ray_inter->vert_inter_wall_hit_y_at = nextInterTouchY;
// 				break;
// 			} else {
// 				nextInterTouchX += ray_inter->xstep;
// 				nextInterTouchY += ray_inter->ystep;
// 			}
// 		}

// 	}
	
// 			// Update ray properties
//     	if (ray_inter->wall_inter_type == HORIZONTAL)
// 		{
//     	    ray->hit_wall_x_at = ray_inter->hori_inter_wall_hit_x_at;
//     	    ray->hit_wall_y_at = ray_inter->hori_inter_wall_hit_y_at;
// 			ray_inter->horiz_distance = distanceBetweenPoints(game->player->x, game->player->y, ray->hit_wall_x_at, ray->hit_wall_y_at);
//     	    // ray->distance = distanceBetweenPoints(game->player->x, game->player->y, ray->hit_wall_x_at, ray->hit_wall_y_at);
//     	}
//     	else if (ray_inter->wall_inter_type == VERTICAL)
// 		{
//     	    ray->hit_wall_x_at = ray_inter->vert_inter_wall_hit_x_at;
//     	    ray->hit_wall_y_at = ray_inter->vert_inter_wall_hit_y_at;
// 			ray_inter->vert_distance = distanceBetweenPoints(game->player->x, game->player->y, ray->hit_wall_x_at, ray->hit_wall_y_at);
//     	    // ray->distance = distanceBetweenPoints(game->player->x, game->player->y, ray->hit_wall_x_at, ray->hit_wall_y_at);
//     	}

// 		if (ray_inter->horiz_distance < ray_inter->vert_distance)
// 			ray->distance = ray_inter->horiz_distance;
// 		else if (ray_inter->horiz_distance > ray_inter->vert_distance)
// 			ray->distance = ray_inter->vert_distance;
// 		else
// 		{
//     	    ray->hit_wall_x_at = 0;
//     	    ray->hit_wall_y_at = 0;
//     	    ray->distance = INT_MAX;
//     	}

// }

// void	casting_ray(t_data *game, t_ray *ray, int ray_id)
// {
// 	t_ray_inter *ray_inter = malloc(sizeof(t_ray_inter));
// 	if (!ray_inter)
// 	{
// 		printf("error malloc t_ray_inter\n");
// 		return ;
// 	}
// 	ray_inter->wall_inter_type = UNDEFINED;
// 	ray_inter->hori_inter_wall_hit_x_at = 0;
// 	ray_inter->hori_inter_wall_hit_y_at = 0;
// 	ray_inter->vert_inter_wall_hit_x_at = 0;
// 	ray_inter->vert_inter_wall_hit_y_at = 0;
// 	ray_inter->xintercept = 0;
// 	ray_inter->yintercept = 0;
// 	ray_inter->xstep = 0;
// 	ray_inter->ystep = 0;
// 	ray_inter->horiz_distance = 0;
// 	ray_inter->vert_distance = 0;
// 	find_ray_grid_inter(game, ray, ray_id, ray_inter, HORIZONTAL);
// 	find_ray_grid_inter(game, ray, ray_id, ray_inter, VERTICAL);

// }

void find_ray_grid_inter(void *data, t_ray *ray, int ray_id, t_ray_inter *ray_inter, Intersection type_to_find)
{
    t_data *game;
    double ray_angle;
    double nextInterTouchX;
    double nextInterTouchY;

    game = (t_data *)data;
    // Calculate ray angle based on FOV and ray index
    ray_angle = game->player->rotation_angle - (FOV_ANGLE / 2) + 
                (ray_id * FOV_ANGLE / NUM_RAYS);
    ray->ray_angle = normalizedAngle(ray_angle);
    // if (fabs(ray->ray_angle - 0.784697) < 0.0001)  // If very close to the problem angle
    //     ray->ray_angle += EPSILON;  // Nudge it slightly
    // Check ray facing directions
    int isRayFacingDown = ray->ray_angle > 0 && ray->ray_angle < PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI;
    int isRayFacingLeft = !isRayFacingRight;
    if (type_to_find == HORIZONTAL)
    {
        // Find y-coordinate of closest horizontal grid intersection
        ray_inter->yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE;
        if (isRayFacingDown)
        {
            ray_inter->yintercept += CUBE_SIZE;
        }
        // double angle = tan(ray->ray_angle);
        // if (angle == 0)
        //     angle = 1e30;
        // Find x-coordinate of closest horizontal grid intersection
        ray_inter->xintercept = game->player->x + (ray_inter->yintercept - game->player->y) / tan(ray->ray_angle);

        // Calculate increment steps
        ray_inter->ystep = CUBE_SIZE;
        if (isRayFacingUp)
        {
            ray_inter->ystep *= -1;
        }

        ray_inter->xstep = CUBE_SIZE / tan(ray->ray_angle);
        if (isRayFacingLeft && ray_inter->xstep > 0)
        {
            ray_inter->xstep *= -1;
        }
        if (isRayFacingRight && ray_inter->xstep < 0)
        {
            ray_inter->xstep *= -1;
        }

        nextInterTouchX = ray_inter->xintercept;
        nextInterTouchY = ray_inter->yintercept;

        // Increment until wall hit
        while (nextInterTouchX >= 0 && nextInterTouchX <= WIDTH &&
               nextInterTouchY >= 0 && nextInterTouchY <= HEIGHT)
        {
	    	int checkX = nextInterTouchX;
			int checkY = nextInterTouchY;
			if (isRayFacingUp)
			{
			    checkY = nextInterTouchY - 1;
			}
			else
			{
			    checkY = nextInterTouchY;
			}
            if (is_collision_found(game, checkX, checkY))
            {
                ray_inter->wall_inter_type = HORIZONTAL;
                ray_inter->hori_inter_wall_hit_x_at = checkX;
                //printf("hit x here %d\n", (int)ray_inter->hori_inter_wall_hit_x_at);
                ray_inter->hori_inter_wall_hit_y_at = checkY;
                ray_inter->horiz_distance = distanceBetweenPoints(
                    game->player->x, game->player->y,
                    nextInterTouchX, nextInterTouchY);
                break;
            }
            nextInterTouchX += ray_inter->xstep;
            nextInterTouchY += ray_inter->ystep;
        }
    }
    else if (type_to_find == VERTICAL)
    {
        // Find x-coordinate of closest vertical grid intersection
        ray_inter->xintercept = floor(game->player->x / CUBE_SIZE) * CUBE_SIZE;
        if (isRayFacingRight)
        {
            ray_inter->xintercept += CUBE_SIZE;
        }

        // Find y-coordinate of closest vertical grid intersection
        ray_inter->yintercept = game->player->y + 
            (ray_inter->xintercept - game->player->x) * tan(ray->ray_angle);

        // Calculate increment steps
        ray_inter->xstep = CUBE_SIZE;
        if (isRayFacingLeft)
        {
            ray_inter->xstep *= -1;
        }

        ray_inter->ystep = CUBE_SIZE * tan(ray->ray_angle);
        if (isRayFacingUp && ray_inter->ystep > 0)
        {
            ray_inter->ystep *= -1;
        }
        if (isRayFacingDown && ray_inter->ystep < 0)
        {
            ray_inter->ystep *= -1;
        }

        nextInterTouchX = ray_inter->xintercept;
        nextInterTouchY = ray_inter->yintercept;

        // Increment until wall hit
        while (nextInterTouchX >= 0 && nextInterTouchX <= WIDTH &&
               nextInterTouchY >= 0 && nextInterTouchY <= HEIGHT)
        {
            int checkX = nextInterTouchX;
            if (isRayFacingLeft)
            {
                checkX -= 1;
            }
            int checkY = nextInterTouchY;

            if (is_collision_found(game, checkX, checkY))
            {
                ray_inter->wall_inter_type = VERTICAL;
                ray_inter->vert_inter_wall_hit_x_at = nextInterTouchX;
                ray_inter->vert_inter_wall_hit_y_at = nextInterTouchY;
                ray_inter->vert_distance = distanceBetweenPoints(
                    game->player->x, game->player->y,
                    nextInterTouchX, nextInterTouchY);
                break;
            }
            nextInterTouchX += ray_inter->xstep;
            nextInterTouchY += ray_inter->ystep;
        }
    }

            //    printf("x : %f -- y : %f\t %d -- %d\n", ray_inter->hori_inter_wall_hit_x_at, ray_inter->hori_inter_wall_hit_y_at, (int)ray_inter->hori_inter_wall_hit_x_at, (int)ray_inter->hori_inter_wall_hit_y_at);
    // if (CUBE_SIZE * 22 ==  (int)ray_inter->hori_inter_wall_hit_x_at && (int)ray_inter->hori_inter_wall_hit_y_at == CUBE_SIZE * 17)
    // {
    //     printf("%f - %f\t %d - %d\n",ray_inter->hori_inter_wall_hit_x_at, ray_inter->hori_inter_wall_hit_y_at, (int)ray_inter->hori_inter_wall_hit_x_at, (int)ray_inter->hori_inter_wall_hit_y_at);
    //     DDA(game, game->player->x, game->player->y, CUBE_SIZE * 22, CUBE_SIZE * 17, 0x000000);
        
    // }
    // 1100.003072 - 850.000000         1100 - 850
    // hit x here 1099
    // Update ray properties with the closest intersection
    if (ray_inter->horiz_distance < ray_inter->vert_distance)
    {
        ray->hit_wall_x_at = ray_inter->hori_inter_wall_hit_x_at;
        ray->hit_wall_y_at = ray_inter->hori_inter_wall_hit_y_at;
        ray->distance = ray_inter->horiz_distance;
    }
    else
    {
        ray->hit_wall_x_at = ray_inter->vert_inter_wall_hit_x_at;
        ray->hit_wall_y_at = ray_inter->vert_inter_wall_hit_y_at;
        ray->distance = ray_inter->vert_distance;
    }

    // Correct for fisheye effect
    ray->distance *= cos(ray->ray_angle - game->player->rotation_angle);
}


void casting_ray(t_data *game, t_ray *ray, int ray_id)
{
    t_ray_inter *ray_inter = calloc(1, sizeof(t_ray_inter));
    if (!ray_inter)
    {
        printf("error malloc t_ray_inter\n");
        return;
    }

    ray_inter->wall_inter_type = UNDEFINED;
    ray_inter->horiz_distance = INT_MAX;
    ray_inter->vert_distance = INT_MAX;
    // if (ray_id == 0)
    //     printf("Ray_Angle: %f\n", ray->ray_angle);
    find_ray_grid_inter(game, ray, ray_id, ray_inter, HORIZONTAL);
    find_ray_grid_inter(game, ray, ray_id, ray_inter, VERTICAL);
    free(ray_inter);
}

void	cast_all_rays(void *data)
{
	t_data	*game;
	int		i;
	
	game = (t_data *)data;
	i = 0;
	while (i < NUM_RAYS)
	{
		// cast_ray(game, &game->player->rays[i], i);
		casting_ray(game, &game->player->rays[i], i);
		i++;
	}

}

// void cast_ray(void *data, t_ray *ray, int ray_id)
// {
//     double xintercept, yintercept;
//     double xstep, ystep;
//     t_data *game;

//     game = (t_data *)data;

//     // HORIZONTAL RAY-GRID INTERSECTION
//     int	foundHorzWallHit = 0;
//     double horzWallHitX = 0;
//     double horzWallHitY = 0;


//     double ray_angle = game->player->rotation_angle - (FOV_ANGLE / 2) + 
//                       (ray_id * FOV_ANGLE / NUM_RAYS);
    
//     // Normalize the angle
//     ray->ray_angle = normalizedAngle(ray_angle);

//     // Calculate intercepts
//     if (sin(ray->ray_angle) > 0)
// 	{
//         yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
//     } else {
//         yintercept = floor(game->player->y / CUBE_SIZE) * CUBE_SIZE;
//     }
//     xintercept = game->player->x + (yintercept - game->player->y) / tan(ray->ray_angle);

//     ystep = (sin(ray->ray_angle) > 0) ? CUBE_SIZE : -CUBE_SIZE;
//     xstep = ystep / tan(ray->ray_angle);

//     double nextInterTouchX = xintercept;
//     double nextInterTouchY = yintercept;

//     // Loop through grid
//     while (nextInterTouchX >= 0 && nextInterTouchX <= game->mlx->window_width
// 			&& nextInterTouchY >= 0 && nextInterTouchY <= game->mlx->window_height)
// 	{
//         if (is_collision_found(game, (int)nextInterTouchX, (int)(nextInterTouchY - (ystep < 0 ? 1 : 0)))) {
//             foundHorzWallHit = 1;
//             horzWallHitX = nextInterTouchX;
//             horzWallHitY = nextInterTouchY;
//             break;
//         } else {
//             nextInterTouchX += xstep;
//             nextInterTouchY += ystep;
//         }
//     }

//     // Update ray properties
//     if (foundHorzWallHit)
// 	{
//         ray->hit_wall_x_at = horzWallHitX;
//         ray->hit_wall_y_at = horzWallHitY;
//         ray->distance = distanceBetweenPoints(game->player->x, game->player->y, ray->hit_wall_x_at, ray->hit_wall_y_at);
//     }
// 	else
// 	{
//         ray->hit_wall_x_at = 0`;
//         ray->hit_wall_y_at = 0;
//         ray->distance = INT_MAX;
//     }
// }

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
        // if ((int)game->player->rays[i].hit_wall_x_at == CUBE_SIZE * 22 && (int)game->player->rays[i].hit_wall_y_at == CUBE_SIZE * 17)
        //     printf("Angle %f\n", game->player->rays[i].ray_angle);
		DDA(game, game->player->x, game->player->y, game->player->rays[i].hit_wall_x_at, game->player->rays[i].hit_wall_y_at, i);
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
    // DDA(data, 750.0, 500.0, 22 * CUBE_SIZE, 17 * CUBE_SIZE, 0x00FF00);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->mlx->img, 0, 0);
}