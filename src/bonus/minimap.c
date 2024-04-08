/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/08 14:14:45 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_draw_floor(t_cub3d *cub3d);
static void	_draw_walls(t_cub3d *cub3d);
static void	_draw_pin(t_cub3d *cub3d);

void	start_minimap(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	cub3d->minimap.size.x = UNIT * cub3d->mapdata.max_width;
	cub3d->minimap.size.y = UNIT * cub3d->mapdata.height;
	cub3d->minimap.pos.x = WIDTH - cub3d->minimap.size.x;
	if (cub3d->minimap.size.x > WIDTH)
		cub3d->minimap.pos.x = 0;
	cub3d->minimap.pos.y = 0;
	_draw_floor(cub3d);
	_draw_walls(cub3d);
	_draw_pin(cub3d);
}

void	update_minimap(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	cub3d->minimap.pin->instances->x
		= (int)(cub3d->minimap.pos.x + (cub3d->player.pos.x * UNIT));
	cub3d->minimap.pin->instances->y
		= (int)(cub3d->minimap.pos.y + (cub3d->player.pos.y * UNIT));
}

static void	_draw_floor(t_cub3d *cub3d)
{
	cub3d->minimap.floor = mlx_new_image(cub3d->mlx,
			cub3d->minimap.size.x, cub3d->minimap.size.y);
	if (!cub3d->minimap.floor)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->minimap.floor,
			cub3d->minimap.pos.x, cub3d->minimap.pos.y) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	draw_rect(cub3d->minimap.floor, cub3d->minimap.size, itovect(0, 0), BCOL);
}

static void	_draw_walls(t_cub3d *cub3d)
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
					itovect(UNIT * i.x, UNIT * i.y), FCOL);
			}
			i.x++;
		}
		i.y++;
	}
}

static void	_draw_pin(t_cub3d *cub3d)
{
	cub3d->minimap.pin = mlx_new_image(cub3d->mlx, UNIT, UNIT);
	if (!cub3d->minimap.pin)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->minimap.pin,
			cub3d->minimap.pos.x + (cub3d->mapdata.start_pos.x * UNIT),
			cub3d->minimap.pos.y + (cub3d->mapdata.start_pos.y * UNIT)) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	draw_rect(cub3d->minimap.pin, itovect(UNIT, UNIT), itovect(0, 0), PCOL);
}
