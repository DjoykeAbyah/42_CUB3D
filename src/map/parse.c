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

/**
 * Do this before anything else!
 * 
 * Will terminate program on error so make sure that
 * nothing else is allocated prior to calling this function.
 */
void	parse_map(t_map *map, char *filename)
{
	t_parse	parse;

	ft_printf("\n-----Mapping from %s...\n", filename);
	ft_bzero(&parse, sizeof(parse));
	parse.raw = ft_read_file(filename);
	if (!parse.raw)
		exit(EXIT_FAILURE);
	if (parse_info(map, &parse) == SUCCESS)
	{
		if (parse_grid(map, &parse) == SUCCESS)
		{
			//if (verify_grid(map) == SUCCESS)
				ft_printf("-----READY!-----\n");
			return ;
		}
	}
	clear_map(map);
	exit(EXIT_FAILURE);
}

//For use in terminate function or anytime prior to quitting program.
void	clear_map(t_map	*map)
{
	int	i;

	free(map->width);
	ft_free_strarr(map->grid);
	i = 0;
	while (i < 4)
	{
		if (map->textures[i])
			mlx_delete_texture(map->textures[i]);
		i++;
	}
}

uint8_t	clear_parse(t_parse *parse, char *errmsg, uint8_t end)
{
	if (end)
		free(parse->raw);
	ft_free_strarr(parse->linedata);
	parse->linedata = NULL;
	free(parse->line);
	parse->line = NULL;
	if (errmsg)
	{
		ft_perror("ERROR\ncub3d", "parsing", errmsg);
		return (FAIL);
	}
	return (SUCCESS);
}

