#include "cub3d.h"

double	distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int	is_collision_found(t_data *data, int x, int y)
{
	int	map_gridindexX;
	int	map_gridindexY;

    // in our case the window width/height is the same as map_width/map_height
	if (x < 0 || x > data->mlx->window_width || y < 0 || y > data->mlx->window_width)
	{
		return (1);
	}

	map_gridindexX = floor(x / CUBE_SIZE);
	map_gridindexY = floor(y / CUBE_SIZE);

   
	return (data->world_map[map_gridindexY][map_gridindexX] != 0);
}

// void	cast_ray(t_mlx *mlx, t_ray **ray)
// {
//         int xintercept, yintercept;
//         int xstep, ystep;

//         ///////////////////////////////////////////
//         // HORIZONTAL RAY-GRID INTERSECTION CODE
//         ///////////////////////////////////////////
//         int foundHorzWallHit = 0;
//         int horzWallHitX = 0;
//         int horzWallHitY = 0;

//         // Find the y-coordinate of the closest horizontal grid intersenction
//         yintercept = floor(mlx->player->y / CUBE_SIZE) * CUBE_SIZE;
    

//         // Find the x-coordinate of the closest horizontal grid intersection
//         xintercept = mlx->player->x + (yintercept - mlx->player->y) / tan((*ray)->ray_angle);

//         // Calculate the increment xstep and ystep
//         ystep = CUBE_SIZE;

//         xstep = CUBE_SIZE / tan((*ray)->ray_angle);

//         int nextHorzTouchX = xintercept;
//         int nextHorzTouchY = yintercept;

//         // Increment xstep and ystep until we find a wall
//         while (nextHorzTouchX >= 0 && nextHorzTouchX <= WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= HEIGHT)
//         {
//             if (is_collision_found(mlx, nextHorzTouchX, nextHorzTouchY)) {
//                 foundHorzWallHit = 1;
//                 horzWallHitX = nextHorzTouchX;
//                 horzWallHitY = nextHorzTouchY;
//                 break;
//             } else {
//                 nextHorzTouchX += xstep;
//                 nextHorzTouchY += ystep;
//             }
//         }
// 	    // Calculate both horizontal and vertical distances and choose the smallest value
//         int	horzHitDistance = (foundHorzWallHit) ? distanceBetweenPoints(mlx->player->x, mlx->player->y, horzWallHitX, horzWallHitY)
//             : (int)FLT_MAX;
// 	    // only store the smallest of the distances
//         (*ray)->hit_wall_x_at = horzWallHitX;
//         (*ray)->hit_wall_y_at = horzWallHitY;
//         (*ray)->distance = horzHitDistance;
//         (*ray)->is_vertical_hit_found = horzHitDistance;
// }

// void cast_ray(t_mlx *mlx, t_ray **ray)
// {
//     int xintercept, yintercept;
//     int xstep, ystep;

//     // HORIZONTAL RAY-GRID INTERSECTION
//     int foundHorzWallHit = 0;
//     int horzWallHitX = 0;
//     int horzWallHitY = 0;

//     if (sin((*ray)->ray_angle) > 0) {
//         yintercept = floor(mlx->player->y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
//     } else {
//         yintercept = floor(mlx->player->y / CUBE_SIZE) * CUBE_SIZE;
//     }

//     xintercept = mlx->player->x + (yintercept - mlx->player->y) / tan((*ray)->ray_angle);

//     ystep = (sin((*ray)->ray_angle) > 0) ? CUBE_SIZE : -CUBE_SIZE;
//     xstep = ystep / tan((*ray)->ray_angle);

//     int nextHorzTouchX = xintercept;
//     int nextHorzTouchY = yintercept;

//     while (nextHorzTouchX >= 0 && nextHorzTouchX <= WIDTH &&
//            nextHorzTouchY >= 0 && nextHorzTouchY <= HEIGHT) {
//         if (is_collision_found(mlx, nextHorzTouchX, nextHorzTouchY - (ystep < 0 ? 1 : 0))) {
//             foundHorzWallHit = 1;
//             horzWallHitX = nextHorzTouchX;
//             horzWallHitY = nextHorzTouchY;
//             break;
//         }
//         nextHorzTouchX += xstep;
//         nextHorzTouchY += ystep;
//     }

//     (*ray)->hit_wall_x_at = horzWallHitX;
//     (*ray)->hit_wall_y_at = horzWallHitY;
//     (*ray)->distance = foundHorzWallHit
//         ? distanceBetweenPoints(mlx->player->x, mlx->player->y, horzWallHitX, horzWallHitY)
//         : INT_MAX;
// }


// void cast_rays(t_mlx *mlx)
// {
// 	int	i;
// 	init_rays(mlx);
//     // start first ray subtracting half of the FOV
//     float rayAngle = mlx->player->rotation_angle - (FOV_ANGLE / 2);

//     // loop all columns casting the rays
// 	i = 0;
//     while (mlx->player->rays[i])
// 	{
//         cast_ray(mlx, &mlx->player->rays[i]);
//         rayAngle += FOV_ANGLE / NUM_RAYS;
// 		i++;
//     }
// }


void player_movement(t_data *data)
{
    t_player *player = data->player;

    // Update rotation angle
    player->rotation_angle += player->turn_direction * player->rotation_speed;
    player->rotation_angle = fmod(player->rotation_angle, 2 * PI); // Keep the angle in range [0, 2PI]

    // Calculate movement direction
    int move_step = player->walk_direction * player->move_speed;
    float new_x = player->x + cos(player->rotation_angle) * move_step;
    float new_y = player->y + sin(player->rotation_angle) * move_step;

    if (!is_collision_found(data, new_x, new_y))
	{
    	// Update player position
        player->x = (int)new_x;
        player->y = (int)new_y;
    }
        // player->x = (int)new_x;
        // player->y = (int)new_y;

    // Reset movement flags
    player->walk_direction = 0;
    player->turn_direction = 0;
}



int render(t_data *data)
{
	int	i;
	int	j;
	int map_width;
	int map_height;
	int	mutable_coordinateX;
	int	mutable_coordinateY;
    // Clear screen


	// player_movement(mlx);
	process_movement(data);

	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		while (j < HEIGHT)
		{
            draw_pixel(data->mlx, i, j, 0x000000);
			j++;
		}
		i++;
	}

    // Draw empty white map
    i = 0;
	map_width = data->mlx->cube_size * MAP_COLS;
	map_height = data->mlx->cube_size * MAP_ROWS;
	while (i < map_width)
	{
    	j = 0;
		while (j < map_height)
		{
            draw_pixel(data->mlx, i, j, 0xffffff);
			j++;
		}
		i++;
	}
    // Draw walls
	i = 0;
	while (i < MAP_ROWS)
	{
		j = 0;
		while (j < MAP_COLS)
		{
			if (data->mlx->world_map[i][j] != 0)
			{
				mutable_coordinateX =  data->mlx->cube_size * j;
				mutable_coordinateY =  data->mlx->cube_size * i;
				cube(data->mlx, mutable_coordinateX, mutable_coordinateY, 0xff0000, 1);
			}
			j++;
		}
		i++;
	
	//  Draw Player	
	circle(data);
	//cast_rays(data->mlx);
	// int	i = 0;
	// while (data->mlx->player->rays[i])
	// {
	// 	line(data->mlx, &i);
	// 	i++;
	// }

    // Display the image
	
    mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img, 0, 0);

	}
    return (0);
}

