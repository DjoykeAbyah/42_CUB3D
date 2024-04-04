/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/04 19:27:43 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		update_minimap_pin(t_cub3d *cub3d);
static uint8_t	move(t_cub3d *cub3d, t_vect dir);
static uint8_t	rotate(t_cub3d *cub3d, uint8_t dir);

/**
 * @todo	update rotation based on mouse x and y movement
*/
void	move_and_render(void *param)
{
	uint8_t	moved;
	t_cub3d	*cub3d;

	moved = 0;
	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		moved = move(cub3d, cub3d->player.dir);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		moved = move(cub3d, math_rotate_vectors(cub3d->player.dir, -PI / 2));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		moved = move(cub3d, math_rotate_vectors(cub3d->player.dir, PI));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		moved = move(cub3d, math_rotate_vectors(cub3d->player.dir, PI / 2));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_Q))
		moved = rotate(cub3d, -1);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_E))
		moved = rotate(cub3d, 1);
	if (moved)
		render(param);
}

/**
 * rotates player slightly in ROT direction
 * @param dir counterclockwise or clockwise
 * @todo remove printf in final
 * currently rotating WAY too fast...?
*/
static uint8_t	rotate(t_cub3d *cub3d, uint8_t dir)
{
	cub3d->player.dir = math_rotate_vectors(cub3d->player.dir, PI / ROT * dir);
	printf("rotating (%.1f, %.1fd)\n",
		cub3d->player.dir.x, cub3d->player.dir.y);
	return (1);
}

/**
 * calculate new player pos based on 
 * key direction of strafing and SPEED
 * @todo remove printf in final
*/
static uint8_t	move(t_cub3d *cub3d, t_vect dir)
{
	t_vect	move;

	move = math_multiply_vectors(dir, SPEED);
	cub3d->player.pos = math_add_vectors(cub3d->player.pos, 0, &move);
	printf("moving (%f, %fd)\n",
		cub3d->player.pos.x, cub3d->player.pos.y);
	update_minimap_pin(cub3d);
	return (1);
}

static void	update_minimap_pin(t_cub3d *cub3d)
{
	cub3d->minimap.pin->instances->x
		= (int)(cub3d->minimap.pos.x + cub3d->player.pos.x * UNIT);
	cub3d->minimap.pin->instances->y
		= (int)(cub3d->minimap.pos.y + cub3d->player.pos.y * UNIT);
}
