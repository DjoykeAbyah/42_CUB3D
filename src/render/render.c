/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/10 15:54:01 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_wall(t_ray *ray);
static void	draw_wall(t_cub3d *cub3d, uint32_t x, uint32_t y);
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
	cub3d->render.ray.dir
		= math_rotate_vectors(cub3d->player.dir, -1 * cub3d->n.half_fov);
	x = 0;
	while (x < WIDTH)
	{
		raytrace(&cub3d->render.ray, cub3d->mapdata.grid, cub3d->n.slice);
		calc_wall(&cub3d->render.ray);
		draw_slice(cub3d, x);
		x++;
	}
}

/**
 * calculate wall height based on distance and populates render
*/
static void	calc_wall(t_ray *ray)
{
	double	wall_dist;

	if (ray->hit_side.x != 0)
	{
		wall_dist = (ray->grid_dist.x - ray->grid_delta.x);
		ray->wall.x = ray->origin->pos.x + wall_dist * ray->dir.x;
	}
	else
	{
		wall_dist = (ray->grid_dist.y - ray->grid_delta.y);
		ray->wall.x = ray->origin->pos.y + wall_dist * ray->dir.y;
	}
	if (wall_dist < 1)
		wall_dist = 1;
	ray->wall.x -= floor(ray->wall.x);
	ray->wall.y = ((int)((HEIGHT / wall_dist) * 0.5));
}

static t_type tx(t_cub3d *cub3d)
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
/**
 * something like this??
*/
static uint32_t pixel_texture(mlx_texture_t *texture, uint32_t x, uint16_t y)
{
	//get rgba of texture function
	int32_t		r;
	int32_t		g;
	int32_t		b;
	uint32_t	rgba;

	r = texture->pixels[(y  * texture->width + x) * texture->bytes_per_pixel];
	g = texture->pixels[(y  * texture->width + x) * texture->bytes_per_pixel + 1];
	b = texture->pixels[(y  * texture->width + x) * texture->bytes_per_pixel + 2];
	rgba = rgba_to_int(r, g, b, 255);
	return (rgba);
}

/**
 * Replace this garbage with getting colour from textures pixel data instead
 * will probably need to use x and y to sample from texture at some point...
 * @todo maybe col * 0.5 for greyscale (shade) fix the uints
 * @note not looping through y and x of the texture only of the wall
 * calculate proportion, get coordinates and get pixel of that coordinate
 * //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
 */	  
static void	draw_wall(t_cub3d *cub3d, uint32_t x, uint32_t y)
{
	double 			scale;
	double			tex_pos;
	mlx_texture_t	texture;
	int 			pixpos_x;
	int				pixpos_y;


	texture = *cub3d->mapdata.textures[tx(cub3d)];
	pixpos_x = (int)(cub3d->render.ray.wall.x * (double)texture.width);
	scale = 1.0 * texture.height / cub3d->render.wall_height;
	if (tx(cub3d) == EAST || tx(cub3d) == NORTH)
		pixpos_x = texture.width - (cub3d->render.ray.wall.x * texture.width) - 1;
	tex_pos = (cub3d->render.wall_start - HEIGHT / 2 + cub3d->render.wall_height / 2) * scale;
	while ((int32_t)y < cub3d->render.wall_end)
	{
		pixpos_y = (int)tex_pos;
		tex_pos += scale;
		mlx_put_pixel(cub3d->render.scene, x, y, pixel_texture(&texture, pixpos_x, pixpos_y));
		y++;
	}
}

/**
 * draws vertical slice.
 * @todo replace colour sampling with texture sampling
*/
static void	draw_slice(t_cub3d *cub3d, uint32_t x)
{
	int32_t		y;

	cub3d->render.wall_start = cub3d->n.half_height - cub3d->render.ray.wall.y;
	cub3d->render.wall_end = cub3d->n.half_height + cub3d->render.ray.wall.y;
	cub3d->render.wall_height = cub3d->render.wall_end - cub3d->render.wall_start;
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
