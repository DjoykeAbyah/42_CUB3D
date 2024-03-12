/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 18:08:39 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/12 19:46:16 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <MLX42/MLX42.h>


#define WIDTH 1024
#define HEIGHT 512

static mlx_image_t* image;

float py = 300;
float px = 300;
int mapX = 8;
int mapY = 8;
int mapS = 64;
int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

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

void draw_map_2d(void *param)
{
	(void)param;
	int x;
	int y;
	int xo;
	int yo;
	uint32_t color;

	y = 0;
	while (y < mapY)
	{
		y++;
		x = 0;
		while (x < mapX)
		{
			x++;
			if (map[y * mapX + x] == 1)
				color = ft_pixel(0, 0, 0, 0);
			else
				color = ft_pixel(255, 255, 255, 255);
			xo = x *mapS;
			yo = y *mapS;
			mlx_put_pixel(image, xo, yo, color);
		}
	}
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
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
	// mlx_loop_hook(mlx, draw_map_2d, mlx);
	mlx_loop_hook(mlx, ft_player, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}