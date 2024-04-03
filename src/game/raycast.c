/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 14:49:28 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/03 14:32:44 by dreijans      ########   odam.nl         */
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
		cub3d->ray.ray_dir.x = cub3d->player.dir.x + (cub3d->ray.plane.x * cub3d->ray.camera.x);
		cub3d->ray.ray_dir.y = cub3d->player.dir.y + (cub3d->ray.plane.y * cub3d->ray.camera.x);
		x++;
	}
}

/**
 * @note getting lenght of ray from any x or y to first x or y
*/
void delta_dist(t_cub3d *cub3d)
{
	cub3d->ray.delta_dist.x = abs(1 / cub3d->ray.ray_dir.x);
	cub3d->ray.delta_dist.y = abs(1 / cub3d->ray.ray_dir.y);
}

void wich_box(t_cub3d *cub3d)
{
	cub3d->ray.map.x = cub3d->player.pos.x;
	cub3d->ray.map.y = cub3d->player.pos.y;
}

/**
 * set a large value for delta_dist x or y if ray_dir x or y is zero
 * It's meant to represent a very large distance, 
 * effectively indicating that the ray is parallel to the y-axis 
 * and won't intersect with anything in the y-direction.
*/
void from_point_to_point(t_cub3d *cub3d)
{
	if (cub3d->ray.ray_dir.x == 0) 
		cub3d->ray.delta_dist.x = 1e30;
	if (cub3d->ray.ray_dir.y == 0) 
		cub3d->ray.delta_dist.y = 1e30;
	else
		delta_dist(cub3d);
}

/**
 * @todo make this a seperate step and side_dist function if that still makes sense
*/
void calc_step_init_side_dist(t_cub3d *cub3d)
{
	if (cub3d->ray.ray_dir.x < 0)
	{
		cub3d->ray.step.x = -1;
		cub3d->ray.side_dist.x = (cub3d->player.pos.x - cub3d->ray.map.x) * cub3d->ray.delta_dist.x;
	}
	else
	{
		cub3d->ray.step.x = 1;
		cub3d->ray.side_dist.x = (cub3d->ray.map.x + 1.0 - cub3d->player.pos.x) * cub3d->ray.delta_dist.x;
	}
	if (cub3d->ray.ray_dir.y < 0)
	{
		cub3d->ray.step.y = -1;
		cub3d->ray.side_dist.y = (cub3d->player.pos.y - cub3d->ray.map.y) * cub3d->ray.delta_dist.y;
	}
	else
	{
		cub3d->ray.step.y = 1;
		cub3d->ray.side_dist.y = (cub3d->ray.map.y + 1.0 - cub3d->player.pos.y) * cub3d->ray.delta_dist.y;
	}
}

/**
 * Dat Dudes Algorithm 
*/
void DDA(t_cub3d *cub3d)
{
	while (cub3d->ray.hit == 0)
	{
		if (cub3d->ray.side_dist.x < cub3d->ray.side_dist.y)
		{
			cub3d->ray.side_dist.x += cub3d->ray.delta_dist.x;
			cub3d->ray.map.x += cub3d->ray.step.x;
			cub3d->ray.side = 1;
		}
		else
		{
			cub3d->ray.side_dist.y += cub3d->ray.delta_dist.y;
			cub3d->ray.map.y += cub3d->ray.step.y;
			cub3d->ray.side = 1;
		}
		if (cub3d->mapdata.grid[cub3d->ray.map.x][cub3d->ray.map.y] > '0')
			cub3d->ray.hit = 1;
	}
}

void calculate_walldist(t_cub3d *cub3d)
{
	if (cub3d->ray.side == 0)
		cub3d->ray.perp_dist = (cub3d->ray.side_dist.x - cub3d->ray.delta_dist.x);
	else
		cub3d->ray.perp_dist = (cub3d->ray.side_dist.y - cub3d->ray.delta_dist.y);

}