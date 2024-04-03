/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/03 17:27:18 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_minimap_pin(t_cub3d *cub3d);
static void	move_player(t_cub3d *cub3d, t_vect dir);
static void change_view(t_cub3d *cub3d, double angle);

void	move_and_render(void *param)
{
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
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_Q))
		change_view(cub3d, -ROT);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_E))
		change_view(cub3d, ROT);
	//rotation based on mouse x and y movement for bonus
	render_viewport(cub3d);
}

/**
 * responsible for changing the player's view direction based on a given angle. 
 * It calculates the cosine and sine of the given angle.
 * It stores the current x player's direction vector (cub3d->player.dir.x) in a temporary variable (tmp_x).
 * It updates the player's direction vector based on the rotation transformation using the calculated cosine and sine values.
 * It rotates the direction vector by multiplying it with a 2x2 rotation matrix.
*/
static void change_view(t_cub3d *cub3d, double angle)
{	
	double cos_val;
	double sin_val;
	double tmp_x;

	cos_val = cos(angle);
	sin_val = sin(angle);
	tmp_x = cub3d->player.dir.x;
	cub3d->player.dir.x = (cos_val * cub3d->player.dir.x) + (-sin_val * cub3d->player.dir.y);
	cub3d->player.dir.y = (sin_val * tmp_x) + (cos_val * cub3d->player.dir.y);
	printf("x = [%f], y = [%f]\n", cub3d->player.dir.x, cub3d->player.dir.y);
}

//calculate new player pos based on current facing direction at SPEED
static void	move_player(t_cub3d *cub3d, t_vect dir)
{
	//update player direction based on input
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
