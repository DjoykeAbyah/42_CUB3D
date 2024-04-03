/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 17:53:01 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/04 01:23:29 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Adds the values of b and c to a, and returns the address of a.
 * @param a Address of the vector to increment
 * @param b Integer to add. Pass 0 for no effect.
 * @param c Pointer to t_vect or t_ivect if relevant, or NULL
*/
t_vect	math_add_vectors(t_vect a, int32_t b, void *c)
{
	t_vect	v;
	t_vect	*p;

	v.x = a.x + b;
	v.y = a.y + b;
	if (c)
	{
		p = c;
		v.x += p->x;
		v.y += p->y;
	}
	return (v);
}

t_vect	math_multiply_vectors(t_vect a, double f)
{
	t_vect	v;

	v.x = a.x * f;
	v.y = a.y * f;
	return (v);
}

/**
 * returns a vector rotated in a direction based on angle
*/
t_vect	math_rotate_vectors(t_vect v, double angle)
{
	t_vect	new;

	new.x = (v.x * cos(angle)) - (v.y * sin(angle));
	new.y = (v.x * sin(angle)) + (v.y * cos(angle));
	return (new);
}

/**
 * moves a vector forward along an angle, at speed
*/
t_vect	*math_move_vector(t_vect *pos, double angle)
{
	pos->x += cos(angle) * SPEED;
	pos->y += sin(angle) * SPEED;
	return (pos);
}
