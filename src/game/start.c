/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 20:51:41 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/05 11:23:11 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_controller(void *param);
static void	setup_render(t_cub3d *cub3d);

void	start_cub3d(t_cub3d *cub3d)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cub3d->mlx)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	mlx_loop_hook(cub3d->mlx, window_controller, cub3d);
	setup_render(cub3d);
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

static void	setup_render(t_cub3d *cub3d)
{
	cub3d->render.scene = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->render.scene)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.scene, 0, 0) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	cub3d->player.pos.x = cub3d->mapdata.start_pos.x;
	cub3d->player.pos.y = cub3d->mapdata.start_pos.y;
	cub3d->player.dir.x = cub3d->mapdata.start_dir.x;
	cub3d->player.dir.y = cub3d->mapdata.start_dir.y;
	cub3d->render.ray.origin = &cub3d->player;
	cub3d->render.ray.halffov = FOV / 2;
	cub3d->render.ray.slice = FOV / WIDTH;
	cub3d->render.ray.map_pos.x = cub3d->player.pos.x;
	cub3d->render.ray.map_pos.y = cub3d->player.pos.y;
	printf("---Spawning player at (%d, %d), direction (%d, %d)\n",
		cub3d->mapdata.start_pos.x, cub3d->mapdata.start_pos.y,
		cub3d->mapdata.start_dir.x, cub3d->mapdata.start_dir.y);
	// render(cub3d);
}
