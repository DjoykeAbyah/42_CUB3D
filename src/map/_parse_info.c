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

static t_type	get_type(char *tag);
static uint8_t	parse_textures(t_map *map, t_type type, char *path);
static uint8_t	parse_colors(t_map *map, t_type type, char *rgbstr);

uint8_t	parse_info(t_map *map, char *line)
{
	char	**linedata;
	uint8_t	status;
	t_type	type;

	status = 0;
	linedata = ft_split(line, ' ');
	if (ft_strarray_count(linedata) != 2)
		ft_perror("cub3d", "could not parse", line);
	else
	{
		type = get_type(linedata[0]);
		if (type < FLOOR)
			status = parse_textures(map, type, linedata[1]);
		else if (type < MAP)
			status = parse_colors(map, type, linedata[1]);
	}
	ft_free_strarr(linedata);
	return (status);
}

static t_type	get_type(char *tag)
{
	if (ft_strcmp("NO", tag) == 0)
		return (NORTH);
	if (ft_strcmp("SO", tag) == 0)
		return (SOUTH);
	if (ft_strcmp("EA", tag) == 0)
		return (EAST);
	if (ft_strcmp("WE", tag) == 0)
		return (WEST);
	if (ft_strcmp("C", tag) == 0)
		return (CEILING);
	else if (ft_strcmp("F", tag) == 0)
		return (FLOOR);
	return (ERROR);
}

static uint8_t	parse_textures(t_map *map, t_type type, char *path)
{
	if (map->textures[type])
	{
		ft_perror("cub3d", "map", "texture already assigned");
		return (0);
	}
	map->textures[type] = mlx_load_png(path);
	if (!map->textures[type])
	{
		ft_perror("cub3d", "could not load texture", path);
		return (0);
	}
	ft_printf("loaded texture: %s of type:%d\n", path, type);
	return (1);
}

static uint8_t	parse_colors(t_map *map, t_type type, char *rgbstr)
{
	char	**coldata;
	uint8_t	rgb[3];
	int		i;

	i = 0;
	coldata = ft_split(rgbstr, ',');
	if (!coldata)
		return (0);
	while (i < 3)
	{
		if (!coldata[i])
		{
			ft_free_strarr(coldata);
			ft_perror("cubed", "bad rgb value", rgbstr);
			return (0);
		}
		rgb[i] = (uint8_t)ft_atoi(coldata[i]);
		i++;
	}
	map->cols[type - FLOOR] = rgba_to_int(rgb[0], rgb[1], rgb[2], 1);
	ft_free_strarr(coldata);
	ft_printf("parsed colour: %s of type:%d\n", rgbstr, type);
	return (1);
}
