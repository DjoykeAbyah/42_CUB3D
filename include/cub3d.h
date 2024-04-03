/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl> 		          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dliu          #+#    #+#                 */
/*   Updated: 2024/03/15 20:41:44 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <math.h>

# include "MLX42/MLX42.h"
# include "libft.h"
# include "utils.h"
# include "parse.h"
# include "game.h"

typedef struct s_vect
{
	float	x;
	float	y;
}	t_vect;

typedef struct s_ivect
{
	int	x;
	int	y;
}	t_ivect;

typedef struct s_player
{
	t_vect		pos;
	t_vect		dir;
}	t_player;

typedef struct s_minimap
{
	t_ivect		pos;
	t_ivect		size;
	mlx_image_t	*pin;
	mlx_image_t	*walls;
	mlx_image_t	*floor;
}	t_minimap;

typedef struct s_map
{
	char			**grid;
	mlx_texture_t	*textures[4];
	int32_t			cols[2];
	uint32_t		height;
	uint32_t		*width;
	uint32_t		max_width;
	t_ivect			start_pos;
	t_ivect			start_dir;
}	t_map;

/**
 * @param camera		normalised position of camera in plane
 * @param plane 		camera plane -1 to 1.
 * @param rayDir 		direction raycast of slice in x of plane.
 * @param map 			grid coordinate in int.
 * @param sideDist 		lenght of ray in rayDir from player pos
 * 						on grid to first whole x or y coordinate.
 * @param deltaDist 	lenght of ray in rayDir from whole x or y 
 * 						coordinate to the next whole x or y coordinate.
 * @param perpWallDist	perpenducular distance from camera plane to wall.
 * @param step			determines what direction to step in.
 * @param hit			check if wall is hit.
 * @param side			checks if NS or EW side of wall hit
 * 
*/
typedef struct s_ray
{
	t_vect	plane;
	t_vect	camera;
	t_vect	rayDir;
	t_ivect	map;
	t_vect	sideDist;
	t_vect	deltaDist;
	float	perpWallDist;
	t_ivect	step;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_render
{
	mlx_image_t	*walls;
	mlx_image_t	*background;
}	t_render;

typedef struct s_cub3d
{
	t_map		mapdata;
	t_minimap	minimap;
	t_render	render;
	t_ray		ray;
	t_player	player;
	mlx_t		*mlx;
}	t_cub3d;

void	parse_map(t_map *map, char *filename);
void	start_cub3d(t_cub3d *cub3d);
void	terminate(t_cub3d *cub3d, const char *what, const char *why);

//BONUS

void	start_minimap(t_cub3d *cub3d);

#endif
