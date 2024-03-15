/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/15 20:41:44 by dreijans      ########   odam.nl         */
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


//need player_pos vector
//need direction vector
//need plane vector
//these two calculate the 

typedef struct s_data
{
	float		px;//player start x
	float 		py;//player start y
	float		p_delta_y;
	float		p_delta_x;
	float		p_angle;
	double 		angle;
	float 		fov_radians;
	int			rotation;
	int			left_right;
	int			up_down;
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t* background;
} 				t_data;


#endif
