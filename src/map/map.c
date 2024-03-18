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

static void	read_map(t_cub3d *cub3d, int fd);
static void	parse_map(t_cub3d *cub3d);
static void	parse_textures(t_cub3d *cub3d, const char **tags);
static void	parse_colours(t_cub3d *cub3d, const char **tags);

void	map(t_cub3d *cub3d, char *filename)
{
	int	fd;

	ft_printf("-----Reading map...");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(NULL, "on open", strerror(errno));
	read_map(cub3d, fd);
	close(fd);
	ft_printf("Done!-----\n");
	// print_map(cub3d);
	parse_map(cub3d);
}

static void	read_map(t_cub3d *cub3d, int fd)
{
	int		rcount;
	char	buffer[BUFFER_SIZE + 1];
	char	*maptxt;
	char	*tmp;

	rcount = read(fd, buffer, BUFFER_SIZE);
	buffer[rcount] = '\0';
	maptxt = ft_strdup(buffer);
	rcount = read(fd, buffer, BUFFER_SIZE);
	while (rcount > 0 && maptxt)
	{
		buffer[rcount] = '\0';
		tmp = ft_strjoin(maptxt, buffer);
		free(maptxt);
		maptxt = tmp;
		rcount = read(fd, buffer, BUFFER_SIZE);
	}
	cub3d->map.data = ft_split(maptxt, '\n');
	free(maptxt);
	if (!cub3d->map.data)
		terminate(NULL, "malloc", strerror(errno));
}


static void	parse_map(t_cub3d *cub3d)
{
	char	**tags;

	tags = ft_split("NO SO WE EA F C", ' ');
	if (!tags)
		terminate(cub3d, "malloc", "failed to allocate");
	parse_textures(cub3d, tags);
	parse_colors(cub3d, tags);
	ft_free_strarr(tags);
	validate_map(cub3d);
}

static void	parse_textures(t_cub3d *cub3d, const char **tags)
{
	char	**line;
	int		i;

	i = NORTH;
	line = ft_split(cub3d->map.data[i], ' ');
	while (i < FLOOR && line && cub3d->map.data[i])
	{
		if (ft_strcmp(line[0], tags[i]) != 0)
			break ;
		cub3d->map.textures[i] = mlx_load_png(line[1]);
		if (!cub3d->map.textures[i])
			break ;
		i++;
		ft_free_strarr(line);
		line = ft_split(cub3d->map.data[i], ' ');
	}
	ft_free_strarr(line);
	if (i < FLOOR)
	{
		ft_printf("error at i=%d\n", i);
		terminate(cub3d, "map error", "could not load textures");
	}
}

static void	parse_colours(t_cub3d *cub3d, const char **tags)
{
	char	**line;
	char	**values;
	int		rgb[3];
	int		i;

	line = ft_split(cub3d->map.data[CEILING], ' ');
	if (line)
	{
		values = NULL;
		if (ft_strcmp(line[0], tags[CEILING]) == 0)
			values = ft_split(line[1], ',');
		if (!values || ft_strarray_count(values) != 3)
			terminate(cub3d, "parsing", "could not parse colour data");
		i = 0;
		while (i < 3)
		{
			if (!ft_atoi_validate(values[i], &rgb[i]))
				break ;
			i++;
		}
		cub3d->map.fcol = rgba_to_int(rgb[0], rgb[1], rgb[2], 1);
		ft_free_strarr(values);
	}
	line = ft_split(cub3d->map.data[FLOOR], ' ');
	ft_printf("error at i=%d\n", i);
	terminate(cub3d, "map error", "could not load textures");
}
