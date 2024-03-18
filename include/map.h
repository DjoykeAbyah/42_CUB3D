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
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	MAP
};

typedef struct s_cub3d	t_cub3d;

typedef struct s_map
{
	char			**data;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	int32_t			floor;
	int32_t			ceiling;
}	t_map;

void	map(t_cub3d *cub3d, char *filename);

#endif
