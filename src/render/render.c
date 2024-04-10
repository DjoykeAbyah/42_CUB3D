/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/10 13:06:02 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		calc_wall(t_render *render);
static t_type	get_texture(t_cub3d *cub3d);
static void		draw_slice(t_cub3d *cub3d, uint32_t x);

/**
 * Raytracing and rendering
 * @todo remove printf before submitting
*/
void	render(void *param)
{
	uint32_t	x;
	t_cub3d		*cub3d;

	cub3d = param;
	cub3d->render.ray.dir
		= math_rotate_vectors(cub3d->player.dir, -1 * cub3d->n.half_fov);
	x = 0;
	while (x < WIDTH)
	{
		raytrace(&cub3d->render.ray, cub3d->mapdata.grid, cub3d->n.slice);
		calc_wall(&cub3d->render);
		draw_slice(cub3d, x);
		x++;
	}
}

/**
 * calculate wall height based on distance and populates render
*/
static void	calc_wall(t_render *render)
{
	double		wall_dist;
	t_player	*origin;

	origin = render->ray.origin;
	if (render->ray.hit_side.x != 0)
	{
		wall_dist = (render->ray.grid_dist.x - render->ray.grid_delta.x);
		render->wall.x = origin->pos.y + wall_dist * render->ray.dir.y;
	}
	else
	{
		wall_dist = (render->ray.grid_dist.y - render->ray.grid_delta.y);
		render->wall.x = origin->pos.y + wall_dist * render->ray.dir.y;
	}
	if (wall_dist < 1)
		wall_dist = 1;
	render->wall.x -= floor(render->wall.x);
	render->wall.x = TILE * render->wall.x;
	render->wall.y = HEIGHT / wall_dist;
	render->wall_start = 0.5 * (HEIGHT - render->wall.y);
	render->wall_end = 0.5 * (HEIGHT + render->wall.y);
}

/**
 * Replace this garbage with getting colour from textures pixel data instead
 * will probably need to use x and y to sample from texture at some point...
 */
static t_type	get_texture(t_cub3d *cub3d)
{
	t_type	t;

	t = NORTH;
	if (cub3d->render.ray.hit_side.x == 1)
		t = EAST;
	if (cub3d->render.ray.hit_side.x == -1)
		t = WEST;
	if (cub3d->render.ray.hit_side.y == 1)
		t = SOUTH;
	if (cub3d->render.ray.hit_side.y == -1)
		t = NORTH;
	return (t);
}

static void	draw_wall(t_cub3d *cub3d, uint32_t x, uint32_t y)
{
	t_type		t;
	uint8_t		rgba[4];
	int32_t		col;
	uint32_t	pos;
	uint32_t	ty;

	ty = 0;
	t = get_texture(cub3d);
	pos = (int)((cub3d->render.wall.x * 4) + (y * TILE * 4));
	while (ty < cub3d->render.wall.y)
	{
		rgba[0] = cub3d->mapdata.textures[t]->pixels[pos];
		pos += 4;
		rgba[1] = cub3d->mapdata.textures[t]->pixels[pos];
		pos += 4;
		rgba[2] = cub3d->mapdata.textures[t]->pixels[pos];
		pos += 4;
		rgba[3] = cub3d->mapdata.textures[t]->pixels[pos];
		pos += y * TILE * 4;
		col = rgba_to_int(rgba[0], rgba[1], rgba[2], rgba[3]);
		mlx_put_pixel(cub3d->render.scene, x, ty + y, col);
		ty++;
	}
}

/**
 * draws vertical slice.
 * @todo replace colour sampling with texture sampling
*/
static void	draw_slice(t_cub3d *cub3d, uint32_t x)
{
	uint32_t		y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < cub3d->render.wall_start)
			mlx_put_pixel(cub3d->render.scene, x, y,
				cub3d->mapdata.cols[CEILING - FLOOR]);
		if (y >= cub3d->render.wall_start && y < cub3d->render.wall_end)
		{
			draw_wall(cub3d, x, y);
			y = cub3d->render.wall_end;
		}
		if (y >= cub3d->render.wall_end)
			mlx_put_pixel(cub3d->render.scene, x, y,
				cub3d->mapdata.cols[FLOOR - FLOOR]);
		y++;
	}
}
