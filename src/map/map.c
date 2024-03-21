/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_create.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 14:08:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 13:54:19 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint8_t	parse_map(t_map *map);

/**
 * Do this before anything else!
 * 
 * Will terminate program on error so make sure that
 * nothing else is allocated prior to calling this function.
 */
void	init_map(t_map *map, char *filename)
{
	char	*raw;

	ft_printf("\n-----Mapping from %s...\n", filename);
	if (!map)
		return ;
	raw = ft_read_file(filename);
	if (!raw)
		exit(EXIT_FAILURE);
	map->lines = ft_split(raw, '\n');
	free(raw);
	if (!map->lines)
		exit(EXIT_FAILURE);
	if (!parse_map(map))
	{
		clear_map(map);
		exit(EXIT_FAILURE);
	}
	ft_printf("-----READY!-----\n");
}

//For use in terminate function or anytime prior to quitting program.
void	clear_map(t_map	*map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->textures[i])
			mlx_delete_texture(map->textures[i]);
		i++;
	}
	ft_free_strarr(map->lines);
}

static uint8_t	parse_map(t_map *map)
{
	map->pos = 0;

	while (map->pos < MAP)
	{
		if (!map->lines[map->pos])
			return (ft_perror("cub3d", "map", "insufficient data"), 0);
		if (!parse_info(map))
			return (0);
		map->pos++;
	}
	map->grid = &map->lines[map->pos];
	return (1);
	// return (parse_grid(map));
}
