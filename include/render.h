/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/03 22:52:14 by daoyi         ########   odam.nl         */
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
# define ROT 0.4
# define PI 3.1415926535

//minimap
# define UNIT 8
# define BCOL 0x000000FF
# define FCOL 0xFFFFFFFF
# define PCOL 0xFF0000FF

/**
 * @param camera		normalised position of camera in plane
 * @param plane 		camera plane -1 to 1.
 * @param ray_dir 		direction raycast of slice in x of plane.
 * @param map 			grid coordinate in int.
 * @param side_dist 		lenght of ray in ray_dir from player pos
 * 						on grid to first whole x or y coordinate.
 * @param delta_dist 	lenght of ray in ray_dir from whole x or y 
 * 						coordinate to the next whole x or y coordinate.
 * @param perp_dist	perpenducular distance from camera plane to wall.
 * @param step			determines what direction to step in.
 * @param hit			check if wall is hit.
 * @param side			checks if NS or EW side of wall hit
 * 
*/
typedef struct s_ray
{
	t_vect	plane;
	t_vect	camera;
	t_vect	ray_dir;
	t_ivect	map;
	t_vect	side_dist;
	t_vect	delta_dist;
	double	perp_dist;
	t_ivect	step;
	int		hit;
	int		side;
}	t_ray;

void	render_init(void *param);
void	render(void *param);

#endif