/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/05/28 15:35:51 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		calc_wall(t_render *render);
static void		draw_wall(t_cub3d *cub3d, uint32_t x, uint32_t y);
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
		raycast(&cub3d->render.ray, cub3d->mapdata.grid, cub3d->n.slice);
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
	double	wall_dist;

	if (render->ray.hit_side.x != 0)
	{
		wall_dist = (render->ray.grid_dist.x - render->ray.grid_delta.x);
		render->wall.x
			= render->ray.origin->pos.y + wall_dist * render->ray.dir.y;
	}
	else
	{
		wall_dist = (render->ray.grid_dist.y - render->ray.grid_delta.y);
		render->wall.x
			= render->ray.origin->pos.x + wall_dist * render->ray.dir.x;
	}
	render->wall.x -= floor(render->wall.x);
	render->wall.y = (int)(HEIGHT / wall_dist);
}

static t_type	texture_from_hitside(t_cub3d *cub3d)
{
	t_type	t;

	t = NORTH;
	if (cub3d->render.ray.hit_side.x == 1)
		t = WEST;
	if (cub3d->render.ray.hit_side.x == -1)
		t = EAST;
	if (cub3d->render.ray.hit_side.y == 1)
		t = NORTH;
	if (cub3d->render.ray.hit_side.y == -1)
		t = SOUTH;
	return (t);
}

/**
 * Draws pixels from wall texture to screen starting at screen position x,y
*/
static void	draw_wall(t_cub3d *cub3d, uint32_t x, uint32_t y)
{
	double			scale;
	double			tex_pos;
	t_ivect			pixpos;
	mlx_texture_t	*tex;

	tex = cub3d->mapdata.textures[texture_from_hitside(cub3d)];
	if (!tex || tex->width == 0 || tex->height == 0)
		return ;
	pixpos.x = (int)(cub3d->render.wall.x * (double)tex->width) % tex->width;
	scale = (double)tex->height / cub3d->render.wall.y;
	tex_pos = (cub3d->render.wall_start - cub3d->n.half_height
			+ (cub3d->render.wall.y * 0.5)) * scale;
	while ((int32_t)y < cub3d->render.wall_end)
	{
		pixpos.y = (int)tex_pos % tex->height;
		tex_pos += scale;
		mlx_put_pixel(cub3d->render.scene, x, y, tex_pix(tex, pixpos));
		y++;
	}
}

/**
 * draws vertical slice.
 * @note not looping through y and x of the texture only of the wall
 * calculate proportion, get coordinates and get pixel of that coordinate
 */
static void	draw_slice(t_cub3d *cub3d, uint32_t x)
{
	int32_t		y;

	cub3d->render.wall_start = ft_biggest(0, cub3d->n.half_height
			- (cub3d->render.wall.y * 0.5));
	cub3d->render.wall_end = ft_smallest(HEIGHT, cub3d->n.half_height
			+ (cub3d->render.wall.y * 0.5));
	y = 0;
	while (y < HEIGHT)
	{
		if (y < cub3d->render.wall_start)
			mlx_put_pixel(cub3d->render.scene, x, y,
				cub3d->mapdata.cols[CEILING - FLOOR]);
		else if (y == cub3d->render.wall_start)
		{
			draw_wall(cub3d, x, y);
			y = cub3d->render.wall_end;
		}
		else if (y >= cub3d->render.wall_end)
			mlx_put_pixel(cub3d->render.scene, x, y,
				cub3d->mapdata.cols[FLOOR - FLOOR]);
		y++;
	}
}
