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

uint8_t	parse_grid(t_map *map)
{
	uint32_t	x;
	uint32_t	y;

	if (!map->lines[map->height])
		return (ft_perror("cub3d", "map", "insufficient data"), FAIL);
	y = map->height;
	map->width = 0;
	while (map->lines[y])
	{
		x = 0;
		while (map->lines[y][x])
			x++;
		if (x > map->width)
			map->width = x;
		y++;
	}
	map->height -= y;
	map->grid = ft_calloc(map->height, sizeof(*(map->grid)));
	if (!map->grid)
		return (FAIL);
	y = 0;
	while (y < map->height)
	{
		map->grid[y] = ft_calloc(map->width, sizeof(**(map->grid)));
		if (!map->grid[y])
		{
			ft_free_strarr(map->grid);
			return (FAIL);
		}
	}
}

uint8_t	check_spaces(t_map *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == ' ')
			{
				if (find_walls(map, x, y, map->grid[y][x]) != SUCCESS)
					return (FAIL);
			}
			x++;
		}
		y++;
	}
	
}

uint8_t	find_wall(t_map *map, uint32_t x, uint32_t y, char c)
{
	uint32_t	pos_x;
	uint32_t	pos_y;
	uint8_t		status;

	//find wall north
	status = FAIL;
	pos_y = y;
	while (pos_y)
	{
		y--;
	}
	
	//find wall east
	pos_x = x;
	while (map->grid[y][pos_x])
	{
		pos_x++;
	}
	
	//find wall south
	pos_y = y;
	while (map->grid[pos_y][x])
	{
		pos_y++;
	}
	
	//find wall west
	pos_x = x;
	while (map->grid[])
	{
		pos_x--;
	}
}