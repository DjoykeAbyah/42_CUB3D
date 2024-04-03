/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/04 01:29:13 by daoyi         ########   odam.nl         */
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
# define PI 3.1415926535

//minimap
# define UNIT 8
# define BCOL 0x000000FF
# define FCOL 0xFFFFFFFF
# define PCOL 0xFF0000FF

// typedef struct s_ray
// {
// 	t_vect	plane;
// 	t_vect	camera;
// 	t_vect	dir;
// 	t_ivect	map;
// 	t_vect	side_dist;
// 	t_vect	delta_dist;
// 	double	perp_dist;
// 	t_ivect	step;
// 	int		hit;
// 	int		side;
// }	t_ray;

typedef struct s_ray
{
	double	angle;
	t_vect	grid_pos;
	t_vect	tile_pos;
}	t_ray;

void	render_init(void *param);
void	render(void *param);

#endif