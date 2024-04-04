/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/04 19:37:44 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_ray(t_ray *ray);
static void	find_wall(t_cub3d *cub3d);
static void	calc_distances(t_ray *ray);
static void	calc_heights(t_cub3d *cub3d);
static void	draw_slice(t_cub3d *cub3d, uint32_t x);

//not rotating??
static void	cast_ray(t_ray *ray)
{
	ray->dir = math_rotate_vectors(ray->dir, -1 * ray->slice);
	printf("raydir (%f, %f)\n", ray->dir.x, ray->dir.y);
}

void	render(void *param)
{
	uint32_t	x;
	t_cub3d		*cub3d;

	cub3d = param;
	cub3d->render.ray.dir
		= math_rotate_vectors(cub3d->player.dir, cub3d->render.ray.halffov);
	x = 0;
	while (x < WIDTH)
	{
		calc_distances(&cub3d->render.ray);
		find_wall(cub3d);
		calc_heights(cub3d);
		draw_slice(cub3d, x);
		x++;
		cast_ray(&cub3d->render.ray);
	}
}

/**
 * calculates player dist from grid and delta between gridlines
*/
static void	calc_distances(t_ray *ray)
{
	//delta
	if (ray->dir.x != 0)
		ray->grid_delta.x = fabs(1 / ray->dir.x);
	else
		ray->grid_delta.x = 1;
	if (ray->dir.y != 0)
		ray->grid_delta.y = fabs(1 / ray->dir.y);
	else
		ray->grid_delta.y = 1;
	//dist
	if (ray->dir.x < 0)
		ray->grid_dist.x = ray->origin->pos.x - ray->map_pos.x;
	else
		ray->grid_dist.x = ray->map_pos.x + 1 - ray->origin->pos.x;
	ray->grid_dist.x *= ray->grid_delta.x;
	if (ray->dir.y < 0)
		ray->grid_dist.y = ray->origin->pos.y - ray->map_pos.y;
	else
		ray->grid_dist.y = ray->map_pos.y + 1 - ray->origin->pos.y;
	ray->grid_dist.y *= ray->grid_delta.y;
	printf("delta(%f, %f) dist(%f, %f)\n", ray->grid_delta.x, ray->grid_delta.y, ray->grid_dist.x, ray->grid_dist.y);
}

/**
 * traces the ray until it finds a wall
*/
static void	find_wall(t_cub3d *cub3d)
{
	t_ray	*ray;
	uint8_t	hit;
	t_ivect	step;

	ray = &cub3d->render.ray;
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
		if (cub3d->mapdata.grid[ray->map_pos.y][ray->map_pos.x] > '0')
			hit = 1;
	}
	printf("W\n");
}

/**
 * calculate wall height based on distance and populates render
*/
static void	calc_heights(t_cub3d *cub3d)
{
	//garbage
	cub3d->render.wall_start = HEIGHT / 4;
	cub3d->render.wall_end = HEIGHT - (HEIGHT / 4);
	printf("H\n");
}

static void	draw_slice(t_cub3d *cub3d, uint32_t x)
{
	uint32_t	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y >= cub3d->render.wall_start && y < cub3d->render.wall_end)
		{
			//depending on direction, sample from texture.
			//for now it just puts garbage
			mlx_put_pixel(cub3d->render.scene, x, y, PCOL);
		}
		else if (y < HEIGHT / 2)
			mlx_put_pixel(cub3d->render.scene, x, y, cub3d->mapdata.cols[1]);
		else
			mlx_put_pixel(cub3d->render.scene, x, y, cub3d->mapdata.cols[0]);
		y++;
	}
	printf("S\n");
}
