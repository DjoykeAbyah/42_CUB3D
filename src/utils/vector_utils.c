/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/04 13:07:58 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ivect	get_sign(void *src)
{
	t_vect	*v;
	t_ivect	new;

	v = src;
	if (v->x < 0)
		new.x = -1;
	else
		new.x = 1;
	if (v->y < 0)
		new.y = -1;
	else
		new.y = 1;
	return (new);
}

//returns a t_ivect of integers (x, y)
t_ivect	itovect(uint32_t x, uint32_t y)
{
	t_ivect	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

//returns a t_vect of doubles (x, y)
t_vect	ftovect(double x, double y)
{
	t_vect	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}
