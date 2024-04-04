/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 20:51:41 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/04 19:40:06 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_controller(void *param);

void	start_cub3d(t_cub3d *cub3d)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cub3d->mlx)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	mlx_loop_hook(cub3d->mlx, window_controller, cub3d);
	render_init(cub3d);
	start_minimap(cub3d);
	mlx_loop_hook(cub3d->mlx, move_and_render, cub3d);
	mlx_loop(cub3d->mlx);
}

static void	window_controller(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		terminate(cub3d, NULL, NULL);
}
