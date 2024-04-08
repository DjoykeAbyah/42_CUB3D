/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/08 19:33:52 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	calc_height(t_ray *ray);
static uint32_t	get_col(t_cub3d *cub3d, uint32_t x, uint32_t y);
static void		draw_slice(t_cub3d *cub3d, uint32_t wall_height, uint32_t x);

/**
 * Raytracing and rendering
 * @todo remove printf before submitting
*/
void	render(void *param)
{
	uint32_t	x;
	t_cub3d		*cub3d;
	uint32_t	half_wall;

	cub3d = param;
	cub3d->render.ray.dir
		= math_rotate_vectors(cub3d->player.dir, -1 * cub3d->n.half_fov);
	x = 0;
	while (x < WIDTH)
	{
		raytrace(&cub3d->render.ray, cub3d->mapdata.grid, cub3d->n.slice);
		half_wall = calc_height(&cub3d->render.ray);
		draw_slice(cub3d, half_wall, x);
		x++;
	}
}

/**
 * calculate wall height based on distance and populates render
*/
static uint32_t	calc_height(t_ray *ray)
{
	double	wall_dist;

	if (ray->hit_side.x != 0)
		wall_dist = (ray->grid_dist.x - ray->grid_delta.x);
	else
		wall_dist = (ray->grid_dist.y - ray->grid_delta.y);
	if (wall_dist < 1)
		wall_dist = 1;
	return ((int)((HEIGHT / wall_dist) * 0.5));
}

/**
 * Replace this garbage with getting colour from textures pixel data instead
 * will probably need to use x and y to sample from texture at some point...
 */
static uint32_t	get_col(t_cub3d *cub3d, uint32_t x, uint32_t y)
{
	uint32_t	col;

	col = x;
	if (cub3d->render.ray.hit_side.x == 1)
		col *= XCOL1;
	if (cub3d->render.ray.hit_side.x == -1)
		col *= XCOL2;
	if (cub3d->render.ray.hit_side.y == 1)
		col *= YCOL1;
	if (cub3d->render.ray.hit_side.y == -1)
		col *= YCOL2;
	return (col * y);
}

/**
 * draws vertical slice.
 * @todo replace colour sampling with texture sampling
*/
static void	draw_slice(t_cub3d *cub3d, uint32_t half_wall, uint32_t x)
{
	int32_t		y;
	int32_t		start;
	int32_t		end;

	start = cub3d->n.half_height - half_wall;
	end = cub3d->n.half_height + half_wall;
	y = 0;
	while (y < HEIGHT)
	{
		if (y >= start && y < end)
		{
			mlx_put_pixel(cub3d->render.scene, x, y,
				get_col(cub3d, x, y));
		}
		else if (y < cub3d->n.half_height)
			mlx_put_pixel(cub3d->render.scene, x, y, cub3d->mapdata.cols[1]);
		else
			mlx_put_pixel(cub3d->render.scene, x, y, cub3d->mapdata.cols[0]);
		y++;
	}
}
