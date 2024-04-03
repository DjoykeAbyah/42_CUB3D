/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 20:12:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/03 21:47:41 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
