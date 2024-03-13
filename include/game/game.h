/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/13 16:38:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../LIBFT/include/libft.h"
# include "../utils/utils.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>

#define WIDTH 1024
#define HEIGHT 512
#define TILE_SIZE 60
#define FOV 60
#define ROTATION_SPEED 0,045 
#define PLAYER_SPEED 4 
#define PI 3.1415926535

typedef struct s_player
{
	int			player_x;
	int 		player_y;
	double 		angle;
	float 		fov_radians;
	int			rotation;
	int			left_right;
	int			up_down;
} 				t_player;

#endif
