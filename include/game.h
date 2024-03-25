/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/22 16:54:08 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H 

# include "cub3d.h"

# define WIDTH 1024 
# define HEIGHT 512
# define TILE_SIZE 8
# define FOV 8
# define ROTATION_SPEED 0.045 
# define PLAYER_SPEED 4 
# define PI 3.1415926535

typedef struct s_cub3d	t_cub3d;

void	mlx_start(t_cub3d *cub3d);

#endif
