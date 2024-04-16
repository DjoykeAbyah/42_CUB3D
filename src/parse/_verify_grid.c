/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _verify_grid.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/25 17:24:24 by dliu          #+#    #+#                 */
/*   Updated: 2024/04/16 19:10:33 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint8_t	verify_enclosed(t_map *map, uint32_t x, uint32_t y);
static uint8_t	check_player(t_map *map, uint32_t x, uint32_t y);
static uint8_t	check_zero(t_map *map, uint32_t	x, uint32_t	y);

uint8_t	verify_grid(t_map *map)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (check_player(map, x, y) != SUCCESS)
				return (ft_perror("cub3d", "invalid starting position",
						map->grid[y]), FAIL);
			if (verify_enclosed(map, x, y) != SUCCESS)
				return (ft_perror("cub3d", "not enclosed", map->grid[y]), FAIL);
			x++;
		}
		y++;
	}
	if (map->start_pos.x == 0)
		return (ft_perror("cub3d", "bad map", "no start position"), FAIL);
	return (SUCCESS);
}

static uint8_t	check_zero(t_map *map, uint32_t	x, uint32_t	y)
{
	if (map->grid[y][x] == '0')
	{
		if (y > 0 && map->width[y - 1] <= x)
			return (FAIL);
		if (y > 0 && map->width[y - 1] > x
			&& map->grid[y - 1][x] != '0' && map->grid[y - 1][x] != '1')
			return (FAIL);
		if (y < map->height - 1 && map->width[y + 1] <= x)
			return (FAIL);
		if (y < map->height - 1 && map->width[y + 1] > x
			&& map->grid[y + 1][x] != '0' && map->grid[y + 1][x] != '1')
		{
			if (check_player(map, x, y) != SUCCESS)
				return (FAIL);
		}
	}
	return (SUCCESS);
}

static uint8_t	verify_enclosed(t_map *map, uint32_t x, uint32_t y)
{
	if ((y == 0 || y == map->height - 1 || x == 0 || x == map->width[y] - 1)
		&& map->grid[y][x] != '1' && map->grid[y][x] != ' ')
		return (FAIL);
	if (map->grid[y][x] == ' ')
	{
		if (y < map->height - 1 && map->width[y + 1] > x
			&& map->grid[y + 1][x] != ' ' && map->grid[y + 1][x] != '1')
			return (FAIL);
		if (y > 0 && map->width[y - 1] > x
			&& map->grid[y - 1][x] != ' ' && map->grid[y - 1][x] != '1')
			return (FAIL);
		if (x > 0 && map->grid[y][x - 1] != '1'
			&& map->grid[y][x - 1] != ' ')
			return (FAIL);
		if (x < map->width[y] - 1 && map->grid[y][x + 1] != '1'
			&& map->grid[y][x + 1] != ' ')
			return (FAIL);
	}
	if (check_zero(map, x, y) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

static uint8_t	check_player(t_map *map, uint32_t x, uint32_t y)
{
	if (map->grid[y][x] != '1'
			&& map->grid[y][x] != '0'
				&& map->grid[y][x] != ' ')
	{
		if (map->start_dir.x != 0 || map->start_dir.y != 0)
			return (FAIL);
		if (x == 0 || y == 0 || x == map->width[y] || y == map->height)
			return (FAIL);
		if (map->grid[y][x] == 'N')
			map->start_dir.y = -1;
		else if (map->grid[y][x] == 'S')
			map->start_dir.y = 1;
		else if (map->grid[y][x] == 'E')
			map->start_dir.x = 1;
		else if (map->grid[y][x] == 'W')
			map->start_dir.x = -1;
		else
			return (FAIL);
		map->start_pos.x = x;
		map->start_pos.y = y;
		map->grid[y][x] = '0';
	}
	return (SUCCESS);
}
