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

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"

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

typedef struct s_parse
{
	char		*raw;
	char		*line;
	char		**linedata;
	uint32_t	start;
	uint32_t	end;
	t_type		type;
	uint8_t		count;
}	t_parse;

# define FAIL 0
# define SUCCESS 1

typedef struct s_map	t_map;

void	clear_map(t_map	*map);
uint8_t	parse_info(t_map *map, t_parse *parse);
uint8_t	parse_grid(t_map *map, t_parse *parse);
uint8_t	clear_parse(t_parse *parse, char *errmsg, uint8_t end);
uint8_t	verify_grid(t_map *map);

#endif
