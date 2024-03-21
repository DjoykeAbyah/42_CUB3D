/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 20:51:41 by dliu          #+#    #+#                 */
/*   Updated: 2024/03/21 20:55:01 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_start(t_cub3d *cub3d)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cub3d->mlx)
	{
		printf("%s", mlx_strerror(mlx_errno));
		terminate(cub3d, "mlx", "could not init mlx");
	}
	// if (!(background = mlx_new_image(mlx, WIDTH, HEIGHT)))//background
	// {
	// 	mlx_close_window(mlx);
	// 	printf("%s", mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (mlx_image_to_window(mlx, background, 0, 0) == -1)
	// {
	// 	mlx_close_window(mlx);
	// 	printf("%s", mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (!(image = mlx_new_image(mlx, 8, 8)))//draw player
	// {
	// 	mlx_close_window(mlx);
	// 	printf("%s", mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (mlx_image_to_window(mlx, image, px, py) == -1)
	// {
	// 	mlx_close_window(mlx);
	// 	printf("%s", mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// mlx_loop_hook(mlx, draw_map_2d, mlx);
	// mlx_loop_hook(mlx, ft_player, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	// return (EXIT_SUCCESS);
}