/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/08 18:08:16 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/08 18:30:02 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "cub3d.h"

typedef struct s_minimap
{
	t_ivect		pos;
	t_ivect		size;
	mlx_image_t	*pin;
	mlx_image_t	*walls;
	mlx_image_t	*floor;
}	t_minimap;

void	start_minimap(void *param);
void	update_minimap(t_minimap *minimap, t_vect pos);

#endif