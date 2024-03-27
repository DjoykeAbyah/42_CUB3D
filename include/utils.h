/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 16:19:27 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/27 18:22:16 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

typedef struct s_ivect	t_ivect;

int32_t	rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
t_ivect	itovect(uint32_t x, uint32_t y);
void	draw_rect(mlx_image_t *img, t_ivect size, t_ivect pos, uint32_t col);

#endif