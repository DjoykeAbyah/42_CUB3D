/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/05 14:31:32 by daoyi         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H 

# include "cub3d.h"

# define WIDTH 1024
# define HEIGHT 512

# define TILE 64
# define FOV 60
# define SPEED 1
# define ROT 120
# define PI 3.14159265358979323846

//temporary colours
# define XCOL1 0xFF0000FF
# define XCOL2 0x0FF000FF
# define YCOL1 0x00FF00FF
# define YCOL2 0x000FF0FF

//minimap
# define UNIT 8
# define BCOL 0x000000FF
# define FCOL 0xFFFFFFFF
# define PCOL 0xFF0000FF

typedef struct s_player
{
	t_vect		pos;
	t_vect		dir;
}	t_player;

/**
 * @param origin		pointer to player struct in cub3d
 * @param grid_delta	angled distance between gridlines
 * @param grid_dist		distance of position from next gridline
 * @param step			check int positive or negative direction of map
*/
typedef struct s_ray
{
	t_player	*origin;
	t_vect		dir;
	t_vect		grid_delta;
	t_vect		grid_dist;
	t_ivect		map_pos;
	t_ivect		hit_side;
}	t_ray;

void	render(void *param);

#endif