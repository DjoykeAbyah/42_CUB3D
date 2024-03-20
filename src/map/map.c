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

static uint8_t	parse_map(t_map *map, char **raw);

/**
 * Do this before anything else!
 * 
 * Will terminate program on error so make sure that
 * nothing else is allocated prior to calling this function.
 */
void	init_map(t_map *map, char *filename)
{
	char	*raw;
	char	**lines;

	ft_printf("\n-----Mapping from %s...\n", filename);
	if (!map)
		return ;
	raw = ft_read_file(filename);
	if (!raw)
		exit(EXIT_FAILURE);
	lines = ft_split(raw, '\n');
	free(raw);
	if (!lines)
		exit(EXIT_FAILURE);
	// ft_put_strarray_fd(lines, STDOUT_FILENO);
	if (!parse_map(map, lines))
	{
		clear_map(map);
		ft_free_strarr(lines);
		exit(EXIT_FAILURE);
	}
	ft_free_strarr(lines);
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
	ft_free_strarr(map->grid);
}

static uint8_t	parse_map(t_map *map, char **lines)
{
	uint64_t	line;

	line = 0;
	while (line < MAP)
	{
		if (!lines[line])
			return (ft_perror("cub3d", "map", "insufficient data"), 0);
		if (!parse_info(map, lines[line]))
			return (0);
		line++;
	}
	return (1);
	// parse_grid(map, &raw[line]);
}
