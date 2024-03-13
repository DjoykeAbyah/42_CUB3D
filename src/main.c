/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 18:08:39 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/13 18:57:49 by dreijans      ########   odam.nl         */
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
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

void draw_square(mlx_image_t *img, int size, int x_pos, int y_pos, uint32_t color)
{
	int x;
	int y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(img, x_pos + x, y_pos + y, color);
			x++;
		}
		y++;
	}
}

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