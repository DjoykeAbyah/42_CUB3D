/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl> 		          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 19:37:29 by dliu          #+#    #+#                 */
/*   Updated: 2024/03/15 20:41:44 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

enum	e_maptype
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	MAP
};

typedef struct s_cub3d	t_cub3d;

typedef struct s_map
{
	char			**data;
	mlx_texture_t	*textures[6];
	int32_t			fcol;
	int32_t			ccol;
}	t_map;

void	map(t_cub3d *cub3d, char *filename);

#endif
