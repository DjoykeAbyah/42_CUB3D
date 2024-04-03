/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/03 16:42:09 by dreijans      ########   odam.nl         */
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

void	draw_line(uint32_t x, t_cub3d *cub3d)
{
	// uint32_t	color = 0xfcba03;
	// t_ivect	temp;

	// (void)x;
	// temp.x = cub3d->player.pos.x * TILE_SIZE;
	// temp.y = cub3d->player.pos.y * TILE_SIZE;
	// draw_rect(cub3d->render.walls, itovect(64, 64), temp, FCOL);
	uint32_t	y;

	y = cub3d->render.draw_start;	
	while (y < cub3d->render.draw_end)
	{
		mlx_put_pixel(cub3d->render.walls, x, y, cub3d->mapdata.cols[0]);
		y++;
	}
}

