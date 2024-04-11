/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/11 13:58:29 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 *@brief function that stores the col of a pixel in an int32_t
*/
int32_t	rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/**
 * draws a rectangle in image 'i' of size 's' at pos 'p' in color 'c'
*/
void	rect(mlx_image_t *i, t_ivect s, t_ivect p, uint32_t c)
{
	int	x;
	int	y;

	y = 0;
	while (y < s.y)
	{
		x = 0;
		while (x < s.x)
		{
			mlx_put_pixel(i, p.x + x, p.y + y, c);
			x++;
		}
		y++;
	}
}

/**
 * get rgba of texture
 * @todo make color darker for y-sides: R, G and B byte each divided through two 
*/
uint32_t	tex_pix(mlx_texture_t *t, t_ivect pixpos)
{
	int32_t		r;
	int32_t		g;
	int32_t		b;
	int32_t		a;
	uint32_t	rgba;

	r = t->pixels[(pixpos.y * t->width + pixpos.x) * t->bytes_per_pixel];
	g = t->pixels[(pixpos.y * t->width + pixpos.x) * t->bytes_per_pixel + 1];
	b = t->pixels[(pixpos.y * t->width + pixpos.x) * t->bytes_per_pixel + 2];
	a = t->pixels[(pixpos.y * t->width + pixpos.x) * t->bytes_per_pixel + 3];
	rgba = rgba_to_int(r, g, b, a);
	return (rgba);
}

// /**
//  * draws a circle in image 'i' of radius 'r' at point 'p' in color 'c'
// */
// void	draw_circle(mlx_image_t *i, uint32_t r, t_ivect p, uint32_t c)
// {
// 	double		radian;
// 	double		full_circle;
// 	uint32_t	x;
// 	uint32_t	y;

// 	radian = 0;
// 	full_circle = 2 * PI;
// 	while (radian < full_circle)
// 	{
// 		x = (int)(p.x + r * cos(radian));
// 		y = (int)(p.y + r * sin(radian));
// 		mlx_put_pixel(i, x, y, c);
// 		radian += 0.1;
// 	}
// }
