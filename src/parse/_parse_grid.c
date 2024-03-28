/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _parse_grid.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 14:08:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 13:54:19 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint8_t	count_height(t_map *map, t_parse *parse);
uint8_t	copy_map(t_map *map, t_parse *parse);

uint8_t	parse_grid(t_map *map, t_parse *parse)
{
	if (!parse->raw[parse->start])
		return (clear_parse(parse, "insufficient data", 1));
	if (count_height(map, parse) != SUCCESS)
		return (clear_parse(parse, "found consecutive newlines in map", 1));
	parse->end = parse->start;
	if (copy_map(map, parse) != SUCCESS)
		return (clear_parse(parse, "likely malloc fail", 1));
	return (clear_parse(parse, NULL, 1));
}

uint8_t	count_height(t_map *map, t_parse *parse)
{
	while (parse->raw[parse->end])
	{
		if (parse->raw[parse->end] == '\n')
		{
			map->height++;
			parse->end++;
			if (parse->raw[parse->end] == '\n')
				return (FAIL);
		}
		else
			parse->end++;
	}
	map->height++;
	return (SUCCESS);
}

uint8_t	copy_map(t_map *map, t_parse *parse)
{
	uint32_t	y;

	map->grid = ft_calloc(map->height + 1, sizeof(*map->grid));
	map->width = ft_calloc(map->height, sizeof(*map->width));
	if (!map->grid || !map->width)
		return (FAIL);
	y = 0;
	while (y < map->height)
	{
		while (parse->raw[parse->end] && parse->raw[parse->end] != '\n')
			parse->end++;
		map->grid[y] = ft_substr(parse->raw, parse->start,
				parse->end - parse->start);
		ft_printf("%s\n", map->grid[y]);
		if (!map->grid[y])
			return (FAIL);
		map->width[y] = parse->end - parse->start;
		if (map->width[y] > map->max_width)
			map->max_width = map->width[y];
		parse->end++;
		parse->start = parse->end;
		y++;
	}
	return (SUCCESS);
}
