/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/28 18:27:39 by daoyi         ########   odam.nl         */
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
void	draw_rect(mlx_image_t *i, t_ivect s, t_ivect p, uint32_t c)
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
