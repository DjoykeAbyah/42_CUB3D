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

typedef struct s_player
{
	float		x;
	float		y;
	float		rot;
	float		p_delta_y;
	float		p_delta_x;
	float		p_angle;
	double		angle;
	float		fov_radians;
	int			rotation;
	int			left_right;
	int			up_down;
}	t_player;

typedef struct s_map
{
	char			**grid;
	mlx_texture_t	*textures[4];
	int32_t			cols[2];
	uint32_t		height;
	uint32_t		*width;
	t_vect			start_pos;
	t_vect			start_dir;
}	t_map;

typedef struct s_cub3d
{
	t_map		map;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*background;
}	t_cub3d;

void	parse_map(t_map *map, char *filename);
void	mlx_start(t_cub3d *cub3d);
void	terminate(t_cub3d *cub3d, const char *what, const char *why);

#endif
