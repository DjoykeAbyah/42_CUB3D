/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/22 13:30:06 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint8_t	move(t_cub3d *cub3d, t_vect dir);
static uint8_t	rotate(t_cub3d *cub3d, double dir);
static uint8_t	is_wall(char **grid, t_vect oldpos, t_vect newpos);

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
		moved = move(cub3d, math_rotate_vectors
				(cub3d->player.dir, cub3d->n.ninety * -1));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		moved = move(cub3d, math_rotate_vectors
				(cub3d->player.dir, PI));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		moved = move(cub3d, math_rotate_vectors
				(cub3d->player.dir, cub3d->n.ninety));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		moved = rotate(cub3d, cub3d->n.turn * -1);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		moved = rotate(cub3d, cub3d->n.turn);
	if (moved)
		render(param);
}

static uint8_t	is_wall(char **grid, t_vect oldpos, t_vect newpos)
{
	if (grid[(int)oldpos.y][(int)newpos.x] != '0'
		|| grid[(int)newpos.y][(int)oldpos.x] != '0')
		return (1);
	return (0);
}

/**
 * calculate new player pos based on 
 * key direction of strafing and SPEED
 * @todo remove printf in final
*/
static uint8_t	move(t_cub3d *cub3d, t_vect dir)
{
	t_vect	move;
	t_vect	collpos;
	t_vect	collmove;

	collmove = math_multiply_vectors(dir, 0.3);
	collpos = math_add_vectors(cub3d->player.pos, 0, &collmove);
	if (is_wall(cub3d->mapdata.grid, cub3d->player.pos, collpos))
		return (0);
	move = math_multiply_vectors(dir, SPEED);
	cub3d->player.pos = math_add_vectors(cub3d->player.pos, 0, &move);
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
	return (1);
}
