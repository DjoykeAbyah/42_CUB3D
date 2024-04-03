/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 16:19:27 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/03 16:16:19 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

typedef struct s_ivect	t_ivect;
typedef struct s_vect	t_vect;
typedef	struct s_cub3d	t_cub3d;

t_ivect	itovect(uint32_t x, uint32_t y);
t_vect	ftovect(float x, float y);

t_vect	*math_add_vectors(t_vect *a, int32_t b, void *c);
t_vect	*math_multiply_vectors(t_vect *v, float f, void *p);
// t_vect	*math_calc_direction(t_vect *old, t_vect dir);
t_vect	*math_calc_direction_left(t_vect *current_dir, t_vect target_dir);
t_vect	*math_calc_direction_right(t_vect *current_dir, t_vect target_dir);


int32_t	rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void	draw_rect(mlx_image_t *img, t_ivect size, t_ivect pos, uint32_t col);
void	draw_line(uint32_t x, t_cub3d *cub3d);

#endif