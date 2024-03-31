/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 17:53:01 by daoyi         #+#    #+#                 */
/*   Updated: 2024/03/31 23:48:36 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Adds the values of b and c to a, and returns the address of a.
 * @param a Address of the vector to increment
 * @param b Integer to add. Pass 0 for no effect.
 * @param c Pointer to t_vect or t_ivect if relevant, or NULL
 * (Technically doesn't need to return anything, but this way 
 * we can call and use the results of this function in one line, if desired)
*/
t_vect	*math_add_vectors(t_vect *a, int32_t b, void *c)
{
	t_vect	*v;

	a->x += b;
	a->y += b;
	v = c;
	if (v)
	{
		a->x += v->x;
		a->y += v->y;
	}
	return (a);
}

/**
 * Multiplies the elements a vector by factor or another vector if not NULL
 * @param a Address of the vector to multiply
 * @param f Factor to multiple both elements of a vector. Pass 1 for no effect
 * @param p	Address of a t_vect or t_ivect as relevant, or NULL
*/
t_vect	*math_multiply_vectors(t_vect *a, float f, void *p)
{
	t_vect	*v;

	a->x *= f;
	a->y *= f;
	v = p;
	if (p)
	{
		a->x *= v->x;
		a->y *= v->y;
	}
	return (a);
}

/**
 * I think the matrix stuff with the sin and cosine goes here?
 * Can't remember how that corresponds with the input direction though
 * Might be something to do with getting difference between current direction
 * and the target direction (deltaaaaaaa), and figuring out the angle between those two points,
 * dividing it up by how many steps we want to take to get there, and then dividing PI by that amount...?
 * But that means it will never actually reach the target direction... maybe something about lerping?
 * For now it's just quick garbage...
 * Feel free to rename anything or change this entirely.
*/
t_vect	*math_calc_direction(t_vect *current_dir, t_vect target_dir)
{
	//only rotation!!!!
	double cos_val;
	double sin_val;

	cos_val = cos(PI/ROT);
	sin_val = sin(PI/ROT);
	target_dir.x = (cos_val * current_dir->x) - (sin_val * current_dir->y);
	target_dir.y = (sin_val * current_dir->x) + (cos_val * current_dir->y);
	current_dir->x = target_dir.x;
	current_dir->y = target_dir.y;
	return (current_dir);
}