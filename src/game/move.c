/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/01 16:11:31 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_minimap_pin(t_cub3d *cub3d);
static void	move_player(t_cub3d *cub3d, t_vect dir);

void	move_and_render(void *param)
{
	//Q and E for rotation
	//ASWD for up down left right
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_player(cub3d, ftovect(0, -1));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_player(cub3d, ftovect(0, 1));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		move_player(cub3d, ftovect(-1, 0));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		move_player(cub3d, ftovect(1, 0));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		move_player(cub3d, ftovect(-1, 0));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		move_player(cub3d, ftovect(1, 0));
	//rotation based on mouse x and y movement for bonus
	render_viewport(cub3d);
}

//calculate new player pos based on current facing direction at SPEED
static void	move_player(t_cub3d *cub3d, t_vect dir)
{
	//update player direction based on input
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		math_calc_direction_left(&cub3d->player.dir, dir);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		math_calc_direction_right(&cub3d->player.dir, dir);
	else
		cub3d->player.dir.x = dir.x;
		cub3d->player.dir.y = dir.y;
	
	//update player position based on facing direction and speed
	math_add_vectors(&cub3d->player.pos, 0,
		math_multiply_vectors(&cub3d->player.dir, SPEED, NULL));

	printf("(%.1f, %.1fd)\n", cub3d->player.pos.x, cub3d->player.pos.y);
	update_minimap_pin(cub3d);
}

static void	update_minimap_pin(t_cub3d *cub3d)
{
	cub3d->minimap.pin->instances->x
		= (int)(cub3d->minimap.pos.x + cub3d->player.pos.x * UNIT);
	cub3d->minimap.pin->instances->y
		= (int)(cub3d->minimap.pos.y + cub3d->player.pos.y * UNIT);
}
