/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 12:36:54 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/01 12:41:23 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//redraw cub3d->render.walls based on player position and facing direction
void	render_viewport(t_cub3d *cub3d)
{
	//all garbage just to show it's doing something
	t_ivect	temp;

	temp.x = cub3d->player.pos.x * TILE_SIZE;
	temp.y = cub3d->player.pos.y * TILE_SIZE;
	draw_rect(cub3d->render.walls, itovect(64, 64), temp, FCOL);
	//garbaaaaage
}
