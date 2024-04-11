/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dreijans      #+#    #+#                 */
/*   Updated: 2024/04/11 14:37:23 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H 

# include "cub3d.h"

# define WIDTH 1024
# define HEIGHT 512

# define TILE 64
# define FOV 60
# define PITCH 100
# define SPEED 0.02
# define ROT 120
# define PI 3.14159265358979323846

//temporary colours
# define XCOL1 0xFF0000FF
# define XCOL2 0x00FF00FF
# define YCOL1 0x0000FFFF
# define YCOL2 0xFF00FFFF

typedef struct s_player	t_player;

/**
 * @param origin		pointer to player struct in cub3d
 * @param grid_delta	angled distance between gridlines
 * @param grid_dist		distance of position from next gridline
 * @param step			check int positive or negative direction of map
 * @todo why wall start and wall end here in vector form again?
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

typedef struct s_render
{
	t_ray		ray;
	mlx_image_t	*scene;
	t_vect		wall;
	int32_t		wall_start;
	int32_t		wall_end;
}	t_render;

void	render(void *param);
void	raytrace(t_ray *ray, char **grid, double slice);

#endif