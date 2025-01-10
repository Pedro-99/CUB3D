#include "cub3d.h"




// void player_movement(t_mlx *mlx)
// {
//     float	move_step;
//     float	new_player_x;
//     float	new_player_y;

//     // Update the player's rotation angle based on turn direction
//     mlx->player->rotation_angle += mlx->player->turn_direction * mlx->player->rotation_speed;

//     // Calculate the movement step based on walk direction and movement speed
//     move_step = mlx->player->walk_direction * mlx->player->move_speed;

//     // Calculate new player position
//     new_player_x = mlx->player->x + cos(mlx->player->rotation_angle) * move_step;
//     new_player_y = mlx->player->y + sin(mlx->player->rotation_angle) * move_step;

//     // TODO : Add collision detection here if needed
//     // TODO : Check if the new position collides with walls or boundaries

//     // Update player's position
//     mlx->player->x = new_player_x;
//     mlx->player->y = new_player_y;

//     // Reset movement and turning directions after processing
//     mlx->player->walk_direction = 0;
//     mlx->player->turn_direction = 0;
// }

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

    // Update player position
    player->x = (int)new_x;
    player->y = (int)new_y;

    // Reset movement flags
    player->walk_direction = 0;
    player->turn_direction = 0;
}


int render(t_mlx *mlx)
{
	int	i;
	int	j;
	int	centerX;
	int	centerY;
	int	mutable_coordinateX;
	int	mutable_coordinateY;
    // Clear screen
	int	cube_size; // Size of each "tile" on the map


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
    	centerX = (WIDTH / 2) - (mapWidth/ 2);
    	centerY = (HEIGHT / 2) - (mapHeight / 2);
    	i = 0;
	while (i < mapWidth)
	{
    		j = 0;
		while (j < mapHeight)
		{
            		draw_pixel(mlx, centerX + i, centerY + j, 0xffffff);
			j++;
		}
		i++;
	}
    // Draw walls
	i = 0;
	cube_size = mapWidth / 24;
	while (i < MAP_ROWS)
	{
		j = 0;
		while (j < MAP_COLS)
		{
			if (mlx->world_map[i][j] != 0)
			{
				mutable_coordinateX =  centerX + (cube_size * j);
				mutable_coordinateY =  centerY + (cube_size * i);
				cube(mlx, mutable_coordinateX, mutable_coordinateY, 0xff0000, 1);
			}
			j++;
		}
		i++;
	}
	//  Draw Player	

	circle(mlx);
	line(mlx);
	
    // Display the image
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

    return (0);
}

