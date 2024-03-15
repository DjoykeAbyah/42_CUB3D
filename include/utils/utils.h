/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 16:19:27 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/15 20:22:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int32_t 		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void 			draw_square(mlx_image_t *img, int size, int x_pos, int y_pos, uint32_t color);

#endif