/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/03 16:46:01 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H 

# include "cub3d.h"

# define WIDTH 1024
# define HEIGHT 512

# define TILE_SIZE 64

# define FOV 60
# define HEIGHT 32
# define SPEED 0.1
# define ROT 0.4
# define PI 3.1415926535

//minimap
# define UNIT 8
# define BCOL 0x000000FF
# define FCOL 0xFFFFFFFF
# define PCOL 0xFF0000FF

typedef struct s_cub3d	t_cub3d;
typedef struct s_ivect	t_ivect;

void	move_and_render(void *param);
void	raycast(t_cub3d *cub3d);

#endif