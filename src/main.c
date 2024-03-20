/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 18:08:39 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/20 17:33:05 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game/game.h"

/**
 * @note just some messy tryout things, 
 * once i can get it to work how I make it properly
 */

static mlx_image_t* image;
static mlx_image_t* background;

float py = 300;//player start y
float px = 300;//player start x
float player_delta_x;
float player_delta_y;
float player_angle;
int mapX = 8;
int mapY = 8;
int mapS = 64;
int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

/**
 * @brief draws player as seperate image
 * @note make this norm proof
*/
void ft_player(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(255, 255, 0, 255);
			mlx_put_pixel(image, i, y, color);
		}
	}
	// other fnction checking radian value between certain points
	// uint32_t color = ft_pixel(0, 255, 0, 255);
	// mlx_put_pixel(image, py + 5, px, color);
}

/**
 * @note plane x and y for view angle or PI pick one!
 * look at lodev tutorial 
*/
void ft_hook(void* param)
{
	// double angle;
	double new_x = 0.0;
	double new_y = 0.0;
	
	// angle = PI;
	mlx_t* mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	//move direction
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
		//PI * (y--, x--)
	//move direction
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
		//PI
	//turn left
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		// player_angle -= 0.1;
		// if (player_angle < 0)
		// 	player_angle += 2 *PI;
		// player_delta_x = cos(player_angle) * 5;
		// player_delta_y = sin(player_angle) * 5;
		new_x = image->instances[0].x * cos(PI - image->instances[0].y * sin(PI));
		new_y = image->instances[0].x * sin(PI + image->instances[0].y * cos(PI));
		if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT)
		{
			px = new_x;
			py = new_y;
			image->instances[0].x -= new_x;
			image->instances[0].y -= new_y;
    	}
	}
	//turn right
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		// player_angle -= 0.1;
		// if (player_angle > 2 * PI)
		// 	player_angle -= 2 *PI;
		// player_delta_x = cos(player_angle) * 5;
		// player_delta_y = sin(player_angle) * 5;
		
		//this just keeps spinning -= 2
		new_x = image->instances[0].x * cos(-PI - image->instances[0].y * sin(PI));
		new_y = image->instances[0].x * sin(-PI + image->instances[0].y * cos(PI));
		if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT)
		{
			px = new_x;
			py = new_y;
			image->instances[0].x -= new_x;
			image->instances[0].y -= new_y;
    	}
	}
}

/**
 * @param void *param
 * @brief draws map in 2D
 * @todo norm proof it, replace for loops
*/
void draw_map_2d(void *param)
{
	(void)param;
	int x;
	int y;
	int xo;
	int yo;
	uint32_t color;

	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			if (map[y * mapX + x] == 1)
				color = ft_pixel(170, 0, 100, 255);
			else
				color = ft_pixel(10, 10, 10, 255);
			xo = (x * mapS);
			yo = (y * mapS);
			draw_square(background, mapS, xo, yo, color);
		}
	}
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(background = mlx_new_image(mlx, WIDTH, HEIGHT)))//background
	{
		mlx_close_window(mlx);
		printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, background, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 8, 8)))//draw player
	{
		mlx_close_window(mlx);
		printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, px, py) == -1)
	{
		mlx_close_window(mlx);
		printf("%s", mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, draw_map_2d, mlx);
	mlx_loop_hook(mlx, ft_player, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// int32_t main(int argc, char *argv[])
// {
// 	//data_t data;
	
// 	if (argc != 2)
// 		return (0);
// 	//parse_input(argv[1], &data);
// 	//do_math(&data);
// 	//start_mlx(&data);
// 	//clear(&data);
// }