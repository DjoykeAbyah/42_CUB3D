/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 20:51:41 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/04 12:51:22 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_controller(void *param);

void	start_cub3d(t_cub3d *cub3d)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	printf("%s\n", mlx_strerror(mlx_errno));
	if (!cub3d->mlx)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	mlx_loop_hook(cub3d->mlx, window_controller, cub3d);
	cub3d->render.scene = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->render.scene)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.scene, 0, 0) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	printf("---Spawning player at (%d, %d), direction (%d, %d)...\n",
		cub3d->mapdata.start_pos.x, cub3d->mapdata.start_pos.y,
		cub3d->mapdata.start_dir.x, cub3d->mapdata.start_dir.y);
	cub3d->player.pos.x = cub3d->mapdata.start_pos.x * TILE;
	cub3d->player.pos.y = cub3d->mapdata.start_pos.y * TILE;
	cub3d->player.dir.x = cub3d->mapdata.start_dir.x;
	cub3d->player.dir.y = cub3d->mapdata.start_dir.y;
	cub3d->render.ray.origin = &cub3d->player;
	render(cub3d);
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
