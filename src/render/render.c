/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/08 12:40:48 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_ray(t_ray *ray, double dir);
static void	find_wall(t_cub3d *cub3d);
static void	calc_distances(t_ray *ray);
static void	calc_height(t_cub3d *cub3d);
static void	draw_slice(t_cub3d *cub3d, uint32_t x);

/**
 * Raytracing and rendering
 * @todo remove printf before submitting
*/
void	render(void *param)
{
	uint32_t	x;
	t_cub3d		*cub3d;

	cub3d = param;
	cast_ray(&cub3d->render.ray, 0);
	cub3d->render.ray.dir
		= math_rotate_vectors(cub3d->player.dir, -1 * cub3d->n.half_fov);
	x = 0;
	while (x < WIDTH)
	{
		calc_distances(&cub3d->render.ray);
		find_wall(cub3d);
		calc_height(cub3d);
		draw_slice(cub3d, x);
		cast_ray(&cub3d->render.ray, cub3d->n.slice);
		x++;
	}
}

static void	cast_ray(t_ray *ray, double dir)
{
	ray->dir = math_rotate_vectors(ray->dir, dir);
	ray->map_pos.x = ray->origin->pos.x;
	ray->map_pos.y = ray->origin->pos.y;
	// printf("raydir (%f, %f)\n", ray->dir.x, ray->dir.y);
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
		ray->grid_dist.x = (ray->origin->pos.x - ray->map_pos.x);
	else
		ray->grid_dist.x = (ray->map_pos.x + 1 - ray->origin->pos.x);
	ray->grid_dist.x *= ray->grid_delta.x;
	if (ray->dir.y < 0)
		ray->grid_dist.y = (ray->origin->pos.y - ray->map_pos.y);
	else
		ray->grid_dist.y = (ray->map_pos.y + 1 - ray->origin->pos.y);
	ray->grid_dist.y *= ray->grid_delta.y;
	// printf("delta(%f, %f) dist(%f, %f)\n", ray->grid_delta.x, ray->grid_delta.y, ray->grid_dist.x, ray->grid_dist.y);
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
		// printf("Checking map pos (%d %d)\n", ray->map_pos.x, ray->map_pos.y);
		if (cub3d->mapdata.grid[ray->map_pos.y][ray->map_pos.x] > '0')
			hit = 1;
	}
}

/**
 * calculate wall height based on distance and populates render
*/
static void	calc_height(t_cub3d *cub3d)
{
	t_ray	*ray;
	double	wall_dist;
	int		wall_height;

	ray = &cub3d->render.ray;
	if (ray->hit_side.x != 0)
		wall_dist = (ray->grid_dist.x - ray->grid_delta.x);
	else
		wall_dist = (ray->grid_dist.y - ray->grid_delta.y);
	wall_height = (int)(HEIGHT / wall_dist);
	cub3d->render.wall_start = cub3d->n.half_height - (wall_height * 0.5);
	cub3d->render.wall_end = cub3d->n.half_height + (wall_height * 0.5);
	// printf("Got wall height: %d\n", half_wall * 2);
}

/**
 * draws vertical slice.
 * @todo replace colour sampling with texture sampling
*/
static void	draw_slice(t_cub3d *cub3d, uint32_t x)
{
	int32_t	y;
	uint32_t	col;

	y = 0;
	col = XCOL1;
	if (cub3d->render.ray.hit_side.x == 1)
		col = XCOL1;
	if (cub3d->render.ray.hit_side.x == -1)
		col = XCOL2;
	if (cub3d->render.ray.hit_side.y == 1)
		col = YCOL1;
	if (cub3d->render.ray.hit_side.y == -1)
		col = YCOL2;
	while (y < HEIGHT)
	{
		if (y >= cub3d->render.wall_start && y < cub3d->render.wall_end)
			mlx_put_pixel(cub3d->render.scene, x, y, col);
		else if (y < cub3d->n.half_height)
			mlx_put_pixel(cub3d->render.scene, x, y, cub3d->mapdata.cols[1]);
		else
			mlx_put_pixel(cub3d->render.scene, x, y, cub3d->mapdata.cols[0]);
		y++;
	}
}
