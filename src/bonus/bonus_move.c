/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus_move.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/11 14:03:23 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static uint8_t	move(t_cub3d *cub3d, t_vect dir);
static uint8_t	rotate(t_cub3d *cub3d, double dir);
static uint8_t	is_wall(char **grid, t_vect oldpos, t_vect newpos);

void	mouse_look(double xpos, double ypos, void *param)
{
	t_cub3d			*cub3d;
	uint8_t			update;
	static double	old_x;

	cub3d = param;
	(void)ypos;
	update = 0;
	if (old_x < xpos)
		update = rotate(cub3d, cub3d->n.turn);
	else
		update = rotate(cub3d, cub3d->n.turn * -1);
	old_x = xpos;
	if (update)
		render(cub3d);
}

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
	{
		render(param);
		update_minimap(cub3d->bonus, cub3d->player.pos);
	}
}

static uint8_t	is_wall(char **grid, t_vect oldpos, t_vect newpos)
{
	t_ivect	pos;

	pos.x = newpos.x;
	pos.y = newpos.y;
	if (oldpos.x && grid[pos.y][pos.x] != '0')
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
	t_vect	newpos;

	move = math_multiply_vectors(dir, SPEED);
	newpos = math_add_vectors(cub3d->player.pos, 0, &move);
	if (is_wall(cub3d->mapdata.grid, cub3d->player.pos, newpos))
		return (0);
	cub3d->player.pos = newpos;
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
