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
# include "minimap.h"
# include "render.h"

typedef struct s_map
{
	char			**grid;
	mlx_texture_t	*textures[4];
	uint32_t		cols[2];
	uint32_t		height;
	uint32_t		*width;
	uint32_t		max_width;
	t_ivect			start_pos;
	t_ivect			start_dir;
}	t_map;

typedef struct s_render
{
	t_ray		ray;
	mlx_image_t	*scene;
	uint32_t	wall_start;
	uint32_t	wall_end;
	uint8_t		direction;
}	t_render;

typedef struct s_cub3d
{
	t_map		mapdata;
	t_minimap	minimap;
	t_render	render;
	t_player	player;
	t_numbers	n;
	mlx_t		*mlx;
}	t_cub3d;

void	parse_map(t_map *map, char *filename);
void	start_cub3d(t_cub3d *cub3d);
void	move_and_render(void *param);
void	terminate(t_cub3d *cub3d, const char *what, const char *why);

#endif
