/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/13 16:19:27 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/19 00:05:35 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int32_t 	rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a);
void		print_map(t_cub3d *cub3d);
void 		draw_square(mlx_image_t *img, int size, int x_pos, int y_pos, uint32_t color);

#endif