/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/03 20:06:49 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//redraw cub3d->render.walls based on player position and facing direction
void	render_viewport(t_cub3d *cub3d)
{
	uint32_t	x;

	while (x < WIDTH)
	{
		// cast_ray(cub3d);
		trace_ray_till_hit(cub3d);
		// correct_fisheye(cub3d);
		draw_column(cub3d);
		x++;
	}
}

void	init_render(t_cub3d	*cub3d)
{
	cub3d->player.pos.x = cub3d->mapdata.start_pos.x * TILE;
	cub3d->player.pos.y = cub3d->mapdata.start_pos.y * TILE;

}
