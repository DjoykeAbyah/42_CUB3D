/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 20:51:41 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/01 11:25:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_controller(void *param);
static void	prepare_images(t_cub3d *cub3d);

void	start_cub3d(t_cub3d *cub3d)
{
	cub3d->player.pos.x = cub3d->mapdata.start_pos.x;
	cub3d->player.pos.y = cub3d->mapdata.start_pos.y;
	printf("---Spawning player at (%.f, %.f)...\n",
		cub3d->player.pos.x, cub3d->player.pos.y);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cub3d->mlx)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	mlx_loop_hook(cub3d->mlx, window_controller, cub3d);
	prepare_images(cub3d);
	render_viewport(cub3d);
	start_minimap(cub3d);
	mlx_loop_hook(cub3d->mlx, move_and_render, cub3d);
	mlx_loop(cub3d->mlx);
}

static void	window_controller(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub3d->mlx);
		terminate(cub3d, NULL, NULL);
	}
}

static void	prepare_images(t_cub3d *cub3d)
{
	cub3d->render.background = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->render.background)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.background, 0, 0) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	draw_rect(cub3d->render.background, itovect(WIDTH, HEIGHT / 2),
		itovect(0, 0), cub3d->mapdata.cols[CEILING - FLOOR]);
	draw_rect(cub3d->render.background, itovect(WIDTH, HEIGHT / 2),
		itovect(0, HEIGHT / 2), cub3d->mapdata.cols[FLOOR - FLOOR]);
	cub3d->render.walls = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->render.walls)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.walls, 0, 0) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
}
