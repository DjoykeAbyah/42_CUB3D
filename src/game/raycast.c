/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 14:49:28 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/02 16:58:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * raycasting function
 * @todo make init function in main for whole cub3d struct
 * @note makes Daoyi extremely mad, respect the mad.. pointless mathwanking... for now
 * Djoyke remains impartial happy to understand any of it
*/
void raycast(t_cub3d *cub3d)
{
	uint32_t x;

	x = 0;
	while (x < WIDTH)
	{
		cub3d->ray.camera.x = ((2 * x) / WIDTH) - 1; //PISS OFF MATHWANKERS
		cub3d->ray.rayDir.x = cub3d->player.dir.x + (cub3d->ray.plane.x * cub3d->ray.camera.x);
		cub3d->ray.rayDir.y = cub3d->player.dir.y + (cub3d->ray.plane.y * cub3d->ray.camera.x);
		x++;
	}
}

/**
 * @note getting lenght of ray from any x or y to first x or y
*/
void delta_dist(t_cub3d *cub3d)
{
	cub3d->ray.deltaDist.x = abs(1 / cub3d->ray.rayDir.x);
	cub3d->ray.deltaDist.y = abs(1 / cub3d->ray.rayDir.y);
}