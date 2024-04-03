Cosine and sine are two fundamental trigonometric functions commonly used in mathematics and various fields, including physics, engineering, and computer graphics. 

1. **Cosine (cos)**:
   - The cosine of an angle in a right triangle is defined as the ratio of the length of the adjacent side to the length of the hypotenuse. In a unit circle, it represents the x-coordinate of a point on the circle.
   - In trigonometry, the cosine function is periodic with a period of \(2\pi\) radians (or \(360^\circ\)), meaning its values repeat every \(2\pi\) radians.
   - Graphically, the cosine function oscillates between -1 and 1, forming a wave-like pattern.
   - In programming languages and mathematical libraries, cosine is typically implemented as a function that takes an angle (in radians) as input and returns the cosine of that angle.

2. **Sine (sin)**:
   - The sine of an angle in a right triangle is defined as the ratio of the length of the opposite side to the length of the hypotenuse. In a unit circle, it represents the y-coordinate of a point on the circle.
   - Similar to cosine, the sine function is periodic with a period of \(2\pi\) radians (or \(360^\circ\)).
   - Graphically, the sine function also oscillates between -1 and 1, forming a wave-like pattern.
   - Like cosine, in programming languages and mathematical libraries, sine is typically implemented as a function that takes an angle (in radians) as input and returns the sine of that angle.

These functions are fundamental in various mathematical calculations involving angles, rotations, oscillations, and periodic phenomena. In applications such as computer graphics and game development, cosine and sine are commonly used for tasks like rotating objects, calculating trajectories, and simulating waveforms.



/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 13:27:04 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/02 13:41:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_minimap_pin(t_cub3d *cub3d);
// static void	move_player(t_cub3d *cub3d, t_vect dir);
static void	move_player(t_cub3d *cub3d, t_vect dir, int key);
static void change_view(t_cub3d *cub3d, double angle);

void	move_and_render(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		move_player(cub3d, ftovect(0, -1), MLX_KEY_W);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		move_player(cub3d, ftovect(0, 1), MLX_KEY_S);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		move_player(cub3d, ftovect(-1, 0), MLX_KEY_A);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		move_player(cub3d, ftovect(1, 0), MLX_KEY_D);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_Q))
		move_player(cub3d, (t_vect)cub3d->player.pos, MLX_KEY_Q);
		// change_view(cub3d, -ROT);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_E))
		move_player(cub3d, (t_vect)cub3d->player.pos, MLX_KEY_E);
		// change_view(cub3d, ROT);
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
static void	move_player(t_cub3d *cub3d, t_vect dir, int key)
{
	if (key == MLX_KEY_Q)
		change_view(cub3d, -ROT);
	if (key == MLX_KEY_E)
		change_view(cub3d, ROT);
	else
	//update player direction based on input
	// cub3d->player.dir.x = dir.x;
	// cub3d->player.dir.y = dir.y;
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