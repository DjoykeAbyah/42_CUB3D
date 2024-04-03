/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/03 22:59:56 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(void *param)
{
	uint32_t	x;
	t_cub3d		*cub3d;

	cub3d = param;
	x = 0;
	(void)cub3d;
	// while (x < WIDTH)
	// {
	// 	cast_ray(cub3d);
	// 	trace_ray_till_hit(cub3d);
	// 	correct_fisheye(cub3d);
	// 	draw_column(cub3d);
		x++;
	// }
}

void	render_init(void	*param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	cub3d->render.scene = mlx_new_image(cub3d->mlx, WIDTH, HEIGHT);
	if (!cub3d->render.scene)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	if (mlx_image_to_window(cub3d->mlx, cub3d->render.scene, 0, 0) == -1)
		terminate(cub3d, "mlx", mlx_strerror(mlx_errno));
	cub3d->player.pos.x = cub3d->mapdata.start_pos.x * TILE;
	cub3d->player.pos.y = cub3d->mapdata.start_pos.y * TILE;
	cub3d->player.dir.x = cub3d->mapdata.start_dir.x;
	cub3d->player.dir.y = cub3d->mapdata.start_dir.y;
	printf("---Spawning player at (%d, %d), direction (%d, %d)...\n",
		cub3d->mapdata.start_pos.x, cub3d->mapdata.start_pos.y,
		cub3d->mapdata.start_dir.x, cub3d->mapdata.start_dir.y);
	render(cub3d);
}
