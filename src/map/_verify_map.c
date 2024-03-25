/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _verify_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/25 17:24:24 by dliu          #+#    #+#                 */
/*   Updated: 2024/03/25 17:34:59 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

uint8_t	verify_enclosed_space(t_map *map, uint32_t x, uint32_t y);
uint8_t	check_player(t_map *map, uint32_t x, uint32_t y);

uint8_t	verify_map(t_map *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (verify_enclosed(map, x, y) != SUCCESS)
				return (FAIL);
			if (check_player(map, x, y) != SUCCESS)
				return (FAIL);
			x++;
		}
		y++;
	}
}

uint8_t	verify_enclosed(t_map *map, uint32_t x, uint32_t y)
{
	if ((y == 0 || y == map->height || x == 0 || x == map->width[y])
		&& map->grid[y][x] != '1' && map->grid[y][x] != ' ')
		return (FAIL);
	if (map->grid[y][x] == ' ')
	{
		if (y == 0 && map->width[y + 1] >= x
			&& map->grid[y + 1][x] != ' ' && map->grid[y + 1][x] != '1')
			return (FAIL);
		if (y > 0 && map->width[y - 1] >= x
			&& map->grid[y - 1][x] != ' ' && map->grid[y - 1][x] != '1')
			return (FAIL);
	}
	return (SUCCESS);
}

uint8_t	check_player(t_map *map, uint32_t x, uint32_t y)
{
	if (map->grid[y][x] != '1'
		|| map->grid[y][x] != '0'
			|| map->grid[y][x] != ' ')
	{
		return (FAIL);
	}
	return (SUCCESS);
}
