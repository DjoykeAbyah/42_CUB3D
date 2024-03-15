/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/15 20:37:46 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/**
 *@brief function that stores the color of a pixel in an int32_t
*/
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

/**
 *@todo make notes
*/
void draw_square(mlx_image_t *img, int size, int x_pos, int y_pos, uint32_t color)
{
	int x;
	int y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(img, x_pos + x, y_pos + y, color);
			x++;
		}
		y++;
	}
}
