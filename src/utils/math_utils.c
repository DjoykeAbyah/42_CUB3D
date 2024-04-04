/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 17:53:01 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/04 10:39:52 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Adds the values of a, b and c and returns a new vector.
 * @param a the vector to increment
 * @param b Integer to add. Pass 0 for no effect.
 * @param c Pointer to t_vect or t_ivect if relevant, or NULL
 * @returns A vector
*/
t_vect	math_add_vectors(t_vect a, int32_t b, void *c)
{
	t_vect	new;
	t_vect	*p;

	new.x = a.x + b;
	new.y = a.y + b;
	if (c)
	{
		p = c;
		new.x += p->x;
		new.y += p->y;
	}
	return (new);
}

/**
 * Multiplies the values v and f, and returns a new vector.
*/
t_vect	math_multiply_vectors(t_vect v, double f)
{
	t_vect	new;

	new.x = v.x * f;
	new.y = v.y * f;
	return (new);
}

/**
 * Returns a vector rotated in a direction based on angle
*/
t_vect	math_rotate_vectors(t_vect v, double angle)
{
	t_vect	new;

	new.x = (v.x * cos(angle)) - (v.y * sin(angle));
	new.y = (v.x * sin(angle)) + (v.y * cos(angle));
	return (new);
}

/**
 * moves a vector forward along an angle, by amount
*/
// t_vect	math_move_vector(t_vect v, double angle, double amount)
// {
// 	t_vect	new;

// 	new.x = v.x + cos(angle) * amount;
// 	new.y = v.y + sin(angle) * amount;
// 	return (new);
// }
