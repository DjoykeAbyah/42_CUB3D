/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 16:19:27 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/05 14:06:54 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/**
 * @param turn			angle in radians per frame when turning player
 * @param ninety		90 degrees in radians
 * @param sice			angle in radians of ray per screen slice
 * @param half_fov		half of FOV in radians
 * @param half_height	half of HEIGHT
 * @param 
*/
typedef struct s_numbers
{
	double	turn;
	double	ninety;
	double	slice;
	double	half_fov;
	double	half_height;
}	t_numbers;

typedef struct s_vect
{
	double	x;
	double	y;
}	t_vect;

typedef struct s_ivect
{
	int32_t	x;
	int32_t	y;
}	t_ivect;

t_ivect	itovect(uint32_t x, uint32_t y);
t_vect	dtovect(double x, double y);
t_ivect	get_sign(void *src);

t_vect	math_add_vectors(t_vect a, int32_t b, void *c);
t_vect	math_multiply_vectors(t_vect v, double f);
t_vect	math_rotate_vectors(t_vect v, double angle);
// double	math_dot_prod(void *p1, void *p2);

// t_vect	math_move_vector(t_vect v, double angle);

// t_vect	*math_calc_direction(t_vect *old, t_vect dir);
// t_vect	*math_calc_direction_left(t_vect *current_dir, t_vect target_dir);
// t_vect	*math_calc_direction_right(t_vect *current_dir, t_vect target_dir);

int32_t	rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void	draw_rect(mlx_image_t *img, t_ivect size, t_ivect pos, uint32_t col);

#endif