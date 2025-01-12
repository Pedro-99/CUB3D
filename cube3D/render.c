#include "cub3d.h"

int	is_collision_found(t_mlx *mlx, int x, int y)
{
	int	map_gridindexX;
	int	map_gridindexY;

	if (x < 0 || x > mapWidth || y < 0 || y > mapHeight)
	{
		return (1);
	}

	map_gridindexX = floor(x / mlx->cube_size);
	map_gridindexY = floor(y / mlx->cube_size);

	printf("x: %d\ty: %d\tgridX :%d\t gridY: %d\t cell : %d\n", x, y, map_gridindexX, map_gridindexY, mlx->world_map[map_gridindexY][map_gridindexX]);
	return (mlx->world_map[map_gridindexY][map_gridindexX] != 0);
}

void player_movement(t_mlx *mlx)
{
    t_player *player = mlx->player;

    // Update rotation angle
    player->rotation_angle += player->turn_direction * player->rotation_speed;
    player->rotation_angle = fmod(player->rotation_angle, 2 * PI); // Keep the angle in range [0, 2PI]

    // Calculate movement direction
    int move_step = player->walk_direction * player->move_speed;
    float new_x = player->x + cos(player->rotation_angle) * move_step;
    float new_y = player->y + sin(player->rotation_angle) * move_step;

    if (!is_collision_found(mlx, new_x, new_y))
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



int render(t_mlx *mlx)
{
	int	i;
	int	j;
	int map_width;
	int map_height;
	int	mutable_coordinateX;
	int	mutable_coordinateY;
    // Clear screen


	// player_movement(mlx);
	process_movement(mlx);

	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		while (j < HEIGHT)
		{
            draw_pixel(mlx, i, j, 0x000000);
			j++;
		}
		i++;
	}

    // Draw empty white map
    i = 0;
	map_width = mlx->cube_size * MAP_COLS;
	map_height = mlx->cube_size * MAP_ROWS;
	while (i < map_width)
	{
    	j = 0;
		while (j < map_height)
		{
            draw_pixel(mlx, i, j, 0xffffff);
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
			if (mlx->world_map[i][j] != 0)
			{
				mutable_coordinateX =  mlx->cube_size * j;
				mutable_coordinateY =  mlx->cube_size * i;
				cube(mlx, mutable_coordinateX, mutable_coordinateY, 0xff0000, 1);
			}
			j++;
		}
		i++;
	
	//  Draw Player	
	circle(mlx);
	line(mlx);
	
    // Display the image
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

	}
    return (0);
}

