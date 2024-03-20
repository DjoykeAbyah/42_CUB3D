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

# include "MLX42/MLX42.h"

/**
 * @param grid: the map
 * @param textures: array of textures, north south east west
 * @param cols: array of colours, floor and ceiling in that order
*/
typedef struct s_map
{
	char			**grid;
	mlx_texture_t	*textures[4];
	int32_t			cols[2];
}	t_map;

void	init_map(t_map *map, char *filename);
void	clear_map(t_map	*map);
void	print_map(const char **raw);

/**
 * For internal parsing use. Warning: Volatile!!!
*/

typedef enum e_maptype
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	MAP,
	ERROR
}	t_type;

uint8_t	parse_info(t_map *map, char *line);
// uint8_t	parse_mapgrid(t_map *map, char **raw);

#endif
