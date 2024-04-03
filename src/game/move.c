/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/03 22:57:33 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		update_minimap_pin(t_cub3d *cub3d);
static uint8_t	move(t_cub3d *cub3d, t_vect dir);
static uint8_t	rotate(t_cub3d *cub3d, double angle);

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
		moved = move(cub3d, ftovect(0, -1));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		moved = move(cub3d, ftovect(0, 1));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		moved = move(cub3d, ftovect(-1, 0));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		moved = move(cub3d, ftovect(1, 0));
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_Q))
		moved = rotate(cub3d, -ROT);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_E))
		moved = rotate(cub3d, ROT);
	if (moved)
		render(param);
}

/**
 * responsible for changing the player's view direction based on a given angle. 
 * It calculates the cosine and sine of the given angle.
 * It stores the current x player's direction vector
 * 		(cub3d->player.dir.x) in a temporary variable (tmp_x).
 * It updates the player's direction vector based on the rotation transformation
 * 		using the calculated cosine and sine values.
 * It rotates the direction vector by multiplying it with a 2x2 rotation matrix.
*/
static uint8_t	rotate(t_cub3d *cub3d, double angle)
{
	double	cos_val;
	double	sin_val;
	double	tmp_x;

	cos_val = cos(angle);
	sin_val = sin(angle);
	tmp_x = cub3d->player.dir.x;
	cub3d->player.dir.x
		= (cos_val * cub3d->player.dir.x) + (-sin_val * cub3d->player.dir.y);
	cub3d->player.dir.y
		= (sin_val * tmp_x) + (cos_val * cub3d->player.dir.y);
	//remove printf when ready
	printf("rotating (%f, %f)\n", cub3d->player.dir.x, cub3d->player.dir.y);
	return (1);
}

//calculate new player pos based on current facing direction at SPEED
static uint8_t	move(t_cub3d *cub3d, t_vect dir)
{
	//remove the next two lines whenever ready
	cub3d->player.dir.x = dir.x;
	cub3d->player.dir.y = dir.y;
	// if (dir.x < 0)
	// 	math_calc_direction_left(&cub3d->player.dir, dir);
	// else
	// 	math_calc_direction_right(&cub3d->player.dir, dir);

	math_add_vectors(&cub3d->player.pos, 0,
		math_multiply_vectors(&cub3d->player.dir, SPEED, NULL));
	//remove printf when ready
	printf("moving (%.1f, %.1fd)\n", cub3d->player.pos.x / TILE, cub3d->player.pos.y / TILE);
	update_minimap_pin(cub3d);
	return (1);
}

static void	update_minimap_pin(t_cub3d *cub3d)
{
	cub3d->minimap.pin->instances->x
		= (int)(cub3d->minimap.pos.x + (cub3d->player.pos.x / TILE) * UNIT);
	cub3d->minimap.pin->instances->y
		= (int)(cub3d->minimap.pos.y + (cub3d->player.pos.y / TILE) * UNIT);
}
