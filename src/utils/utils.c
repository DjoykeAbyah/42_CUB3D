/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/19 00:06:38 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/**
 *@brief function that stores the col of a pixel in an int32_t
*/
int32_t	rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	print_map(t_cub3d *cub3d)
{
	int	i;

	ft_printf("-----Print Map START-----\n");
	if (!cub3d->map.data)
		return ;
	i = 0;
	while (cub3d->map.data[i])
	{
		ft_printf("%s\n", cub3d->map.data[i]);
		i++;
	}
	ft_printf("-----Print Map END-----\n");
}

/**
 *@todo make notes
*/
void	draw_square(mlx_image_t *img, int size, int x_pos, int y_pos, uint32_t col)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			mlx_put_pixel(img, x_pos + x, y_pos + y, col);
			x++;
		}
		y++;
	}
}
