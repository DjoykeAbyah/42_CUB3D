/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus_minimap.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/22 12:24:50 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	_draw_floor(t_cub3d *cub3d, t_minimap *minimap);
static void	_draw_walls(t_cub3d *cub3d, t_minimap *minimap);
static void	_draw_pin(t_cub3d *cub3d, t_minimap *minimap);

void	start_minimap(void *param)
{
	t_cub3d		*cub3d;
	t_bonus		*bonus;

	cub3d = param;
	bonus = cub3d->bonus;
	bonus->minimap.size.x = UNIT * cub3d->mapdata.max_width;
	bonus->minimap.size.y = UNIT * cub3d->mapdata.height;
	bonus->minimap.pos.x = WIDTH - bonus->minimap.size.x;
	if (bonus->minimap.size.x > WIDTH)
		bonus->minimap.pos.x = 0;
	bonus->minimap.pos.y = 0;
	_draw_floor(cub3d, &bonus->minimap);
	_draw_walls(cub3d, &bonus->minimap);
	_draw_pin(cub3d, &bonus->minimap);
}

void	update_minimap(void *param, t_vect pos)
{
	t_bonus		*bonus;

	bonus = param;
	bonus->minimap.pin->instances->x
		= (int)(bonus->minimap.pos.x + (pos.x * UNIT) - UNIT);
	bonus->minimap.pin->instances->y
		= (int)(bonus->minimap.pos.y + (pos.y * UNIT) - UNIT);
}

static void	_draw_floor(t_cub3d *cub3d, t_minimap *minimap)
{
	minimap->floor
		= mlx_new_image(cub3d->mlx, minimap->size.x, minimap->size.y);
	if (!minimap->floor)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, minimap->floor,
			minimap->pos.x, minimap->pos.y) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	rect(minimap->floor, minimap->size, itovect(0, 0), BCOL);
}

static void	_draw_walls(t_cub3d *cub3d, t_minimap *minimap)
{
	t_ivect		i;

	minimap->walls
		= mlx_new_image(cub3d->mlx, minimap->size.x, minimap->size.y);
	if (!minimap->walls)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, minimap->walls,
			minimap->pos.x, minimap->pos.y) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	i.y = 0;
	while (cub3d->mapdata.grid[i.y])
	{
		i.x = 0;
		while (cub3d->mapdata.grid[i.y][i.x])
		{
			if (cub3d->mapdata.grid[i.y][i.x] == '1')
			{
				rect(minimap->walls, itovect(UNIT, UNIT),
					itovect(UNIT * i.x, UNIT * i.y), FCOL);
			}
			i.x++;
		}
		i.y++;
	}
}

static void	_draw_pin(t_cub3d *cub3d, t_minimap *minimap)
{
	uint32_t	x;
	uint32_t	y;

	x = minimap->pos.x
		+ (cub3d->mapdata.start_pos.x * UNIT) - (UNIT * 0.5);
	y = minimap->pos.y
		+ (cub3d->mapdata.start_pos.y * UNIT) - (UNIT * 0.5);
	minimap->pin = mlx_new_image(cub3d->mlx, UNIT * 2, UNIT * 2);
	if (!minimap->pin)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, minimap->pin, x, y) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	rect(minimap->pin, itovect(UNIT, UNIT), itovect(UNIT / 2, UNIT / 2),
		PCOL);
}
