/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/03/27 19:03:32 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_floor(t_cub3d *cub3d);
static void	draw_walls(t_cub3d *cub3d);
static void	draw_pin(t_cub3d *cub3d);

static void	minimap_input_controller(void *param);

void	start_minimap(t_cub3d *cub3d)
{
	cub3d->minimap.size.x = UNIT * cub3d->mapdata.max_width;
	cub3d->minimap.size.y = UNIT * cub3d->mapdata.height;
	cub3d->minimap.pos.x = WIDTH - cub3d->minimap.size.x;
	if (cub3d->minimap.size.x > WIDTH)
		cub3d->minimap.pos.x = 0;
	cub3d->minimap.pos.y = 0;
	draw_floor(cub3d);
	draw_walls(cub3d);
	draw_pin(cub3d);
	mlx_loop_hook(cub3d->mlx, minimap_input_controller, cub3d);
}

static void	draw_floor(t_cub3d *cub3d)
{
	cub3d->minimap.floor = mlx_new_image(cub3d->mlx,
			cub3d->minimap.size.x, cub3d->minimap.size.y);
	if (!cub3d->minimap.floor)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->minimap.floor,
			cub3d->minimap.pos.x, cub3d->minimap.pos.y) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	draw_rect(cub3d->minimap.floor, cub3d->minimap.size, itovect(0, 0),
		cub3d->mapdata.cols[FLOOR - FLOOR]);
}

static void	draw_walls(t_cub3d *cub3d)
{
	t_ivect		i;

	cub3d->minimap.walls = mlx_new_image(cub3d->mlx,
			cub3d->minimap.size.x, cub3d->minimap.size.y);
	if (!cub3d->minimap.walls)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->minimap.walls,
			cub3d->minimap.pos.x, cub3d->minimap.pos.y) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	i.y = 0;
	while (cub3d->mapdata.grid[i.y])
	{
		i.x = 0;
		while (cub3d->mapdata.grid[i.y][i.x])
		{
			if (cub3d->mapdata.grid[i.y][i.x] == '1')
			{
				draw_rect(cub3d->minimap.walls, itovect(UNIT, UNIT),
					itovect(UNIT * i.x, UNIT * i.y),
					cub3d->mapdata.cols[CEILING - FLOOR]);
			}
			i.x++;
		}
		i.y++;
	}
}

static void	draw_pin(t_cub3d *cub3d)
{
	cub3d->minimap.pin = mlx_new_image(cub3d->mlx, UNIT, UNIT);
	if (!cub3d->minimap.pin)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	cub3d->player.pos.x = cub3d->mapdata.start_pos.x * TILE_SIZE;
	cub3d->player.pos.y = cub3d->mapdata.start_pos.y * TILE_SIZE;
	if (mlx_image_to_window(cub3d->mlx, cub3d->minimap.pin,
			cub3d->minimap.pos.x + (cub3d->mapdata.start_pos.x * UNIT),
			cub3d->minimap.pos.y + (cub3d->mapdata.start_pos.y * UNIT)) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	draw_rect(cub3d->minimap.pin, itovect(UNIT, UNIT),
		itovect(0, 0), rgba_to_int(255, 255, 0, 255));
}

void	minimap_input_controller(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_UP))
		cub3d->minimap.pin->instances[0].y -= SPEED;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_DOWN))
		cub3d->minimap.pin->instances[0].y += SPEED;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		cub3d->minimap.pin->instances[0].x -= SPEED;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		cub3d->minimap.pin->instances[0].x += SPEED;
}
