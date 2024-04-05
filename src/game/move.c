/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/05 11:24:53 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint8_t	move(t_cub3d *cub3d, t_vect dir);
static uint8_t	rotate(t_cub3d *cub3d, double dir);

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
		moved = rotate(cub3d, -PI / ROT);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_E))
		moved = rotate(cub3d, PI / ROT);
	if (moved)
		return ;
		// render(param);
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
	printf("moving (%f, %fd)\n", cub3d->player.pos.x, cub3d->player.pos.y);
	update_minimap(cub3d);
	return (1);
}

/**
 * rotates player slightly in ROT direction
 * @param dir counterclockwise or clockwise
 * @todo remove printf in final. Fix counter-clockwise rotation
 * re-research vector rotation...
*/
static uint8_t	rotate(t_cub3d *cub3d, double dir)
{
	cub3d->player.dir = math_rotate_vectors(cub3d->player.dir, dir);
	printf("rotating (%f, %fd)\n", cub3d->player.dir.x, cub3d->player.dir.y);
	return (1);
}
