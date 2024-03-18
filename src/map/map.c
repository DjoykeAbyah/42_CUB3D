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
static void	print_map(t_cub3d *cub3d);
// static void	parse_map(t_cub3d *cub3d);
// static void	validate_element(t_cub3d *cub3d, int x, int y);

void	map(t_cub3d *cub3d, char *filename)
{
	int	fd;

	ft_printf("Parsing map...");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(NULL, "on open", strerror(errno));
	read_map(cub3d, fd);
	ft_printf("done!\n");
	close(fd);
	print_map(cub3d);
	// parse_map(cub3d);
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

static void	print_map(t_cub3d *cub3d)
{
	int	i;

	ft_printf("Got map:\n");
	if (!cub3d->map.data)
		return ;
	i = 0;
	while (cub3d->map.data[i])
	{
		ft_printf("%s\n", cub3d->map.data[i]);
		i++;
	}
}

// static void	parse_map(t_cub3d *cub3d)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < cub3d->max_size.y)
// 	{
// 		if ((int)ft_strlen(cub3d->map[y]) != cub3d->max_size.x)
// 			terminate(NULL, "map", "inconsistent size");
// 		x = 0;
// 		while (x < cub3d->max_size.x)
// 		{
// 			if ((y == 0 || y == cub3d->max_size.y - 1 || x == 0
// 					|| x == cub3d->max_size.x - 1) && cub3d->map[y][x] != '1')
// 				terminate(NULL, "map", "insufficient walls");
// 			else if (cub3d->map[y][x] == 'P' || cub3d->map[y][x] == 'E'
// 				|| cub3d->map[y][x] == 'C' || cub3d->map[y][x] == 'D')
// 				validate_element(cub3d, x, y);
// 			else if (cub3d->map[y][x] != '0' && cub3d->map[y][x] != '1')
// 				terminate(NULL, "map", "illegal element detected");
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (cub3d->total == 0 || cub3d->door.pos.x == 0 || cub3d->player.pos.x == 0)
// 		terminate(NULL, "map", "missing elements");
// }

// static void	validate_element(t_cub3d *cub3d, int x, int y)
// {
// 	if (cub3d->map[y][x] == 'P')
// 	{
// 		if (cub3d->player.pos.x != 0)
// 			terminate(NULL, "map", "too many player starting positions");
// 		cub3d->player.pos.x = x;
// 		cub3d->player.pos.y = y;
// 		cub3d->map[y][x] = '0';
// 	}
// 	else if (cub3d->map[y][x] == 'E')
// 	{
// 		if (cub3d->door.pos.x != 0)
// 			terminate(NULL, "map", "too many exits");
// 		cub3d->door.pos.x = x;
// 		cub3d->door.pos.y = y;
// 	}
// 	else if (cub3d->map[y][x] == 'D')
// 		bonus_add_death(cub3d, x, y);
// 	else if (cub3d->map[y][x] == 'C')
// 		add_collectible(cub3d, x, y);
// }
