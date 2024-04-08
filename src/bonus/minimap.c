/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/08 18:35:51 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	_draw_floor(t_cub3d *cub3d, t_minimap *minimap);
static void	_draw_walls(t_cub3d *cub3d, t_minimap *minimap);
static void	_draw_pin(t_cub3d *cub3d, t_minimap *minimap);

void	start_minimap(void *param)
{
	t_minimap	minimap;
	t_cub3d		*cub3d;

	cub3d = param;
	minimap.size.x = UNIT * cub3d->mapdata.max_width;
	minimap.size.y = UNIT * cub3d->mapdata.height;
	minimap.pos.x = WIDTH - minimap.size.x;
	if (minimap.size.x > WIDTH)
		minimap.pos.x = 0;
	minimap.pos.y = 0;
	_draw_floor(cub3d->mlx, &minimap);
	_draw_walls(cub3d, &minimap);
	_draw_pin(cub3d, &minimap);
}

void	update_minimap(t_minimap *minimap, t_vect pos)
{
	minimap->pin->instances->x = (int)(minimap->pos.x + (pos.x * UNIT) - UNIT);
	minimap->pin->instances->y = (int)(minimap->pos.y + (pos.y * UNIT) - UNIT);
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
	draw_rect(minimap->floor, minimap->size, itovect(0, 0), BCOL);
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
				draw_rect(minimap->walls, itovect(UNIT, UNIT),
					itovect(UNIT * i.x, UNIT * i.y), FCOL);
			}
			i.x++;
		}
		i.y++;
	}
}

static void	_draw_pin(t_cub3d *cub3d, t_minimap *minimap)
{
	minimap->pin = mlx_new_image(cub3d->mlx, UNIT * 2, UNIT * 2);
	if (!minimap->pin)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, minimap->pin,
			minimap->pos.x + (cub3d->mapdata.start_pos.x * UNIT) - UNIT,
			minimap->pos.y + (cub3d->mapdata.start_pos.y * UNIT) - UNIT) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	draw_rect(minimap->pin, itovect(UNIT, UNIT), itovect(UNIT / 2, UNIT / 2),
		PCOL);
}
