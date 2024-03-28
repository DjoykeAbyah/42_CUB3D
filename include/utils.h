/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 16:19:27 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/28 22:23:41 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

typedef struct s_ivect	t_ivect;
typedef struct s_vect	t_vect;

t_ivect	itovect(uint32_t x, uint32_t y);
t_vect	ftovect(float x, float y);

t_vect	*math_add_vectors(t_vect *a, int32_t b, void *c);
t_vect	*math_multiply_vectors(t_vect *v, float f, void *p);
t_vect	*math_calc_direction(t_vect *old, t_vect dir);

int32_t	rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void	draw_rect(mlx_image_t *img, t_ivect size, t_ivect pos, uint32_t col);

#endif