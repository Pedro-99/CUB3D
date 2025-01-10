#include "cub3d.h"

// int event_handler(int key, t_mlx *mlx)
// {
//     if (key == UP)
//         mlx->player->walk_direction = 1; // Move forward
//     else if (key == DOWN)
//         mlx->player->walk_direction = -1; // Move backward
//     else if (key == LEFT)
//         mlx->player->turn_direction = -1; // Turn left
//     else if (key == RIGHT)
//         mlx->player->turn_direction = 1; // Turn right
//     else if (key == ESC) // Stop movement on ESC key
//     {
//         mlx_destroy_window(mlx->mlx, mlx->win);
//         exit(0);
//     }

//     return (0);
// }

// int key_release_handler(int key, t_mlx *mlx)
// {
//     if (key == UP || key == DOWN)
//         mlx->player->walk_direction = 0;
//     else if (key == LEFT || key == RIGHT)
//         mlx->player->turn_direction = 0;

//     return (0);
// }

int g_keys[256] = {0}; // Array to track key states (pressed or released)


int key_press_handler(int key, t_mlx *mlx)
{
    if (key >= 0 && key < 256)
        g_keys[key] = 1; // Mark the key as pressed

    if (key == ESC) // Exit on ESC key
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    return (0);
}


int key_release_handler(int key, t_mlx *mlx)
{
    (void)mlx;
    if (key >= 0 && key < 256)
        g_keys[key] = 0; // Mark the key as released
    return (0);
}


void process_movement(t_mlx *mlx)
{
    t_player *player = mlx->player;

    if (g_keys[UP])
        player->walk_direction = 1; // Move forward
    if (g_keys[DOWN])
        player->walk_direction = -1; // Move backward
    if (g_keys[LEFT])
        player->turn_direction = -1; // Turn left
    if (g_keys[RIGHT])
        player->turn_direction = 1; // Turn right

    // Apply movement and rotation
    player_movement(mlx);

    // Reset directions for the next frame
    player->walk_direction = 0;
    player->turn_direction = 0;
}
