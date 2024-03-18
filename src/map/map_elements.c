/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_elements.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 18:50:10 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 15:09:05 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_element(t_data *data, int x, int y);
static void	add_collectible(t_data *data, int x, int y);

void	map_elements(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->max_size.y)
	{
		if ((int)ft_strlen(data->map[y]) != data->max_size.x)
			terminate(NULL, "map", "inconsistent size");
		x = 0;
		while (x < data->max_size.x)
		{
			if ((y == 0 || y == data->max_size.y - 1 || x == 0
					|| x == data->max_size.x - 1) && data->map[y][x] != '1')
				terminate(NULL, "map", "insufficient walls");
			else if (data->map[y][x] == 'P' || data->map[y][x] == 'E'
				|| data->map[y][x] == 'C' || data->map[y][x] == 'D')
				validate_element(data, x, y);
			else if (data->map[y][x] != '0' && data->map[y][x] != '1')
				terminate(NULL, "map", "illegal element detected");
			x++;
		}
		y++;
	}
	if (data->total == 0 || data->door.pos.x == 0 || data->player.pos.x == 0)
		terminate(NULL, "map", "missing elements");
}

static void	validate_element(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'P')
	{
		if (data->player.pos.x != 0)
			terminate(NULL, "map", "too many player starting positions");
		data->player.pos.x = x;
		data->player.pos.y = y;
		data->map[y][x] = '0';
	}
	else if (data->map[y][x] == 'E')
	{
		if (data->door.pos.x != 0)
			terminate(NULL, "map", "too many exits");
		data->door.pos.x = x;
		data->door.pos.y = y;
	}
	else if (data->map[y][x] == 'D')
		bonus_add_death(data, x, y);
	else if (data->map[y][x] == 'C')
		add_collectible(data, x, y);
}

static void	add_collectible(t_data *data, int x, int y)
{
	t_collect	**collects;
	int			i;

	collects = malloc((data->total + 1) * sizeof(*collects));
	if (!collects)
		terminate(NULL, "malloc", strerror(errno));
	i = 0;
	while (data->collects && i < data->total)
	{
		collects[i] = data->collects[i];
		i++;
	}
	collects[i] = malloc(sizeof (**collects));
	free(data->collects);
	if (!collects[i])
		terminate(NULL, "malloc", strerror(errno));
	collects[i]->pos.x = x;
	collects[i]->pos.y = y;
	data->collects = collects;
	data->total += 1;
}
