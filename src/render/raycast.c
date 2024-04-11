/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/08 18:42:13 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/10 12:59:58 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_distances(t_ray *ray);
static void	find_wall(t_ray *ray, char **grid);

void	raycast(t_ray *ray, char **grid, double slice)
{
	ray->map_pos.x = ray->origin->pos.x;
	ray->map_pos.y = ray->origin->pos.y;
	calc_distances(ray);
	find_wall(ray, grid);
	ray->dir = math_rotate_vectors(ray->dir, slice);
}

/**
 * calculates player dist from grid and delta between gridlines
*/
static void	calc_distances(t_ray *ray)
{
	if (ray->dir.x != 0)
		ray->grid_delta.x = fabs(1 / ray->dir.x);
	else
		ray->grid_delta.x = 1;
	if (ray->dir.y != 0)
		ray->grid_delta.y = fabs(1 / ray->dir.y);
	else
		ray->grid_delta.y = 1;
	if (ray->dir.x < 0)
		ray->grid_dist.x = (ray->origin->pos.x - ray->map_pos.x);
	else
		ray->grid_dist.x = (ray->map_pos.x + 1 - ray->origin->pos.x);
	ray->grid_dist.x *= ray->grid_delta.x;
	if (ray->dir.y < 0)
		ray->grid_dist.y = (ray->origin->pos.y - ray->map_pos.y);
	else
		ray->grid_dist.y = (ray->map_pos.y + 1 - ray->origin->pos.y);
	ray->grid_dist.y *= ray->grid_delta.y;
}

/**
 * traces the ray until it finds a wall
*/
static void	find_wall(t_ray *ray, char **grid)
{
	uint8_t	hit;
	t_ivect	step;

	step = get_sign(&ray->dir);
	hit = 0;
	while (!hit)
	{
		ray->hit_side = itovect(0, 0);
		if (ray->grid_dist.x < ray->grid_dist.y)
		{
			ray->grid_dist.x += ray->grid_delta.x;
			ray->map_pos.x += step.x;
			ray->hit_side.x = step.x;
		}
		else
		{
			ray->grid_dist.y += ray->grid_delta.y;
			ray->map_pos.y += step.y;
			ray->hit_side.y = step.y;
		}
		if (grid[ray->map_pos.y][ray->map_pos.x] > '0')
			hit = 1;
	}
}
