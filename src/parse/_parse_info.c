/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _parse_info.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/07 14:08:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 13:54:19 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint8_t	parse_type(t_map *map, t_parse *parse);
static uint8_t	parse_textures(t_map *map, t_parse *parse);
static uint8_t	parse_colors(t_map *map, t_parse *parse);

uint8_t	parse_info(t_map *map, t_parse *parse)
{
	parse->end += ft_charcount(parse->raw, '\n');
	parse->start = parse->end;
	while (parse->count < MAP)
	{
		if (!parse->raw[parse->start])
			return (clear_parse(parse, "insufficient data", 1));
		while (parse->raw[parse->end] && parse->raw[parse->end] != '\n')
			parse->end++;
		parse->line = ft_substr(parse->raw, parse->start,
				parse->end - parse->start);
		parse->linedata = ft_split(parse->line, ' ');
		if (!parse->line || !parse->linedata)
			return (clear_parse(parse, "malloc fail", 1));
		if (ft_strarray_count(parse->linedata) != 2)
			return (clear_parse(parse, "bad line in map", 1));
		if (parse_type(map, parse) != SUCCESS)
			return (clear_parse(parse, "could not parse texture or colour", 1));
		clear_parse(parse, NULL, 0);
		parse->end += ft_charcount(&parse->raw[parse->end], '\n');
		parse->start = parse->end;
		parse->count++;
	}
	return (clear_parse(parse, NULL, 0));
}

static uint8_t	parse_type(t_map *map, t_parse *parse)
{
	if (ft_strcmp("NO", parse->linedata[0]) == 0)
		parse->type = NORTH;
	else if (ft_strcmp("SO", parse->linedata[0]) == 0)
		parse->type = SOUTH;
	else if (ft_strcmp("EA", parse->linedata[0]) == 0)
		parse->type = EAST;
	else if (ft_strcmp("WE", parse->linedata[0]) == 0)
		parse->type = WEST;
	else if (ft_strcmp("C", parse->linedata[0]) == 0)
		parse->type = CEILING;
	else if (ft_strcmp("F", parse->linedata[0]) == 0)
		parse->type = FLOOR;
	else
		return (FAIL);
	if (parse->type < FLOOR)
		return (parse_textures(map, parse));
	else if (parse->type < MAP)
		return (parse_colors(map, parse));
	return (SUCCESS);
}

static uint8_t	parse_textures(t_map *map, t_parse *parse)
{
	if (map->textures[parse->type])
		return (FAIL);
	map->textures[parse->type] = mlx_load_png(parse->linedata[1]);
	if (!map->textures[parse->type])
		return (FAIL);
	ft_printf("loaded texture: %s: %d\n", parse->linedata[1], parse->type);
	return (SUCCESS);
}

static uint8_t	parse_colors(t_map *map, t_parse *parse)
{
	char	**coldata;
	uint8_t	rgb[3];
	int		validate;
	int		i;

	coldata = ft_split(parse->linedata[1], ',');
	if (!coldata)
		return (FAIL);
	i = 0;
	while (i < 3)
	{
		if (!coldata[i] || !ft_atoi_validate(coldata[i], &validate)
			|| validate > 255 || validate < 0)
			return (ft_free_strarr(coldata), FAIL);
		rgb[i] = (uint8_t)validate;
		i++;
	}
	if (coldata[i])
		return (ft_free_strarr(coldata), FAIL);
	map->cols[parse->type - FLOOR] = rgba_to_int(rgb[0], rgb[1], rgb[2], 255);
	ft_printf("parsed color: %s: %d\n", parse->linedata[1], parse->type);
	return (ft_free_strarr(coldata), SUCCESS);
}
