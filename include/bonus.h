/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: daoyi <daoyi@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/08 18:08:16 by daoyi         #+#    #+#                 */
/*   Updated: 2024/04/11 13:21:32 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "cub3d.h"

//minimap
# define UNIT 8
# define BCOL 0x000000FF
# define FCOL 0xFFFFFFFF
# define PCOL 0xFF0000FF

typedef struct s_minimap
{
	t_ivect		pos;
	t_ivect		size;
	mlx_image_t	*pin;
	mlx_image_t	*walls;
	mlx_image_t	*floor;
}	t_minimap;

typedef struct s_bonus
{
	t_minimap	minimap;
	t_ivect		mousepos;
}	t_bonus;

void	start_minimap(void *param);
void	update_minimap(void *param, t_vect pos);
void	mouse_look(double xpos, double ypos, void *param);

#endif