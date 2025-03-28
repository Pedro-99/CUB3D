#include "cub3d.h"

void cube(t_mlx *mlx, int x, int y, int color, int type)
{
	(void)type;

    for (int i = 1; i < CUBE_SIZE; i++)
    {
        for (int j = 1; j < CUBE_SIZE; j++)
            draw_pixel(mlx, x + i, y + j, color);
    }
}


void circle(t_data *data)
{
    int x, y;

    for (x = -data->player->radius; x <= data->player->radius; x++)
    {
        for (y = -data->player->radius; y <= data->player->radius; y++)
        {
            if (x * x + y * y <= data->player->radius * data->player->radius)
            {
                draw_pixel(data->mlx, data->player->x + x, data->player->y + y, 0x00ff00);
            }
        }
    }
}

// Function to draw a line using Bresenham's algorithm
void draw_line(t_mlx *mlx, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // Draw the current point
        draw_pixel(mlx, x1, y1, color);

        // Check if we've reached the endpoint
        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;

        // Adjust x and y based on the error term
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_dda_line(t_mlx *mlx, double x1, double y1, double x2, double y2, int color)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double steps;
    
    // Determine the number of steps needed
    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
    
    // Calculate increment values
    double x_increment = dx / steps;
    double y_increment = dy / steps;
    
    // Starting position
    double x = x1;
    double y = y1;
    
    // Draw initial point
    draw_pixel(mlx, x1, y1, color);
    
    // Draw the line
    for (int i = 0; i < steps; i++)
    {
        x += x_increment;
        y += y_increment;
        draw_pixel(mlx, x, y, color);
    }
}

// // Function to calculate the end point of the line and draw it
// void line(t_mlx *mlx, int *ray_id)
// {
//     int x1 = mlx->player->x; // Starting point (player's position)
//     int y1 = mlx->player->y;
//     float line_length = distanceBetweenPoints(x1, y1, mlx->player->rays[*ray_id]->hit_wall_x_at, mlx->player->rays[*ray_id]->hit_wall_y_at); // Length of the line
//     float angle = mlx->player->rotation_angle;

//     // Calculate the end point of the line
//     int x2 = x1 + cos(angle) * line_length;
//     int y2 = y1 + sin(angle) * line_length;

//     // Draw the line using Bresenham's algorithm
//     draw_line(mlx, x1, y1, x2, y2, 0x00FF00); // Green color
// }


void line(t_data *data, int len)
{
    // TODO - draw line from (p.x, p.y to wall_hit.x, wall_hit.y)
    int x, y;
   // float line_length = 100.0; // Length of the line
    float angle = data->player->rotation_angle;

    for (int i = 0; i < len; i++)
    {
        x = data->player->x + cos(angle) * i;
        y = data->player->y + sin(angle) * i;
        draw_pixel(data->mlx, x, y, 0x00ff00); // Draw line in green
    }
}


int abs(int n) { return ((n > 0) ? n : (n * (-1))); } 
  
// DDA Function for line generation 
void DDA(t_data *data, double X0, double Y0, double X1, double Y1, int x) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0;
    float angle = data->player->rotation_angle;
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  (void)angle;
    // calculate increment in x & y for each steps 
    // float Xinc = (dx / (float)steps); 
    // float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    // printf("(%f, %f)\t(%f, %f)\n", X0, Y0, X1, Y1);
    // printf("Player (%f, %f)\t(%d, %d)\n", X0, Y0, (int)X0 / CUBE_SIZE, (int)Y0 / CUBE_SIZE);
    int color = 0x000000;
    // if (X1 == CUBE_SIZE * 22 && Y1 == CUBE_SIZE * 17)
    // {
    //     color = 0xFF0000;
    // }
    draw_dda_line(data->mlx, X0, Y0, X1, Y1, color);
    // printf("X : %2.f Y : %2.f\tX0 : %2.f Y0 : %d\n", X, Y, X0, Y0);
    // draw_line(data->mlx, X0, Y0, X1, Y1, 0x000000);
    // for (int i = 0; i <= steps; i++) {
    //     draw_pixel(data->mlx, floor(X), floor(Y), 0x000000); // put pixel at (X,Y) 
    //     X += Xinc; // increment in x at each step 
    //     Y += Yinc; // increment in y at each step 
    //     //delay(100); // for visualization of line- 
    //                 // generation step by step 
    // } 
}