/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 20:51:41 by dliu          #+#    #+#                 */
/*   Updated: 2024/03/22 17:14:48 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap(void *param);
static void	draw_player(void *param);
static void	input_controller(void *param);

void	mlx_start(t_cub3d *cub3d)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cub3d->mlx)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	cub3d->background = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->background)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->background, 0, 0) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	cub3d->image = mlx_new_image(cub3d->mlx, 8, 8);
	if (!cub3d->image)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->image,
			cub3d->player.x, cub3d->player.y) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	draw_minimap(cub3d);
	draw_player(cub3d);
	mlx_loop_hook(cub3d->mlx, input_controller, cub3d);
	mlx_loop(cub3d->mlx);
}

/**
 * @brief	draws minimap
*/
static void	draw_minimap(void *param)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	t_cub3d		*cub3d;

	cub3d = param;
	y = 0;
	while (cub3d->map.grid[y])
	{
		x = 0;
		while (cub3d->map.grid[y][x])
		{
			if (cub3d->map.grid[y][x] == 1)
				color = rgba_to_int(170, 0, 100, 255);
			else
				color = rgba_to_int(10, 10, 10, 255);
			draw_square(cub3d->background,
				TILE_SIZE, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief	draws player as seperate image
*/
static void	draw_player(void *param)
{
	uint32_t	x;
	uint16_t	y;
	uint32_t	color;
	t_cub3d		*cub3d;

	cub3d = param;
	y = 0;
	while (y < cub3d->image->height)
	{
		x = 0;
		while (x < cub3d->image->width)
		{
			color = rgba_to_int(255, 255, 0, 255);
			mlx_put_pixel(cub3d->image, x, y, color);
			x++;
		}
		y++;
	}
}

static void	input_controller(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_UP))
		cub3d->image->instances[0].y -= 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_DOWN))
		cub3d->image->instances[0].y += 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		cub3d->image->instances[0].x -= 5;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		cub3d->image->instances[0].x += 5;
}
