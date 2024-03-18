/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 15:27:48 by dliu          #+#    #+#                 */
/*   Updated: 2023/03/02 13:46:58 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game)
{
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*desk;
	t_pos			pos;

	wall = load_image(game, "./art/wall.png");
	floor = load_image(game, "./art/floor.png");
	desk = load_image(game, "./art/desk.png");
	pos.y = 0;
	while (pos.y < game->data->max_size.y)
	{
		pos.x = 0;
		while (pos.x < game->data->max_size.x)
		{
			if (game->data->map[pos.y][pos.x] != '1')
				draw(game, floor, pos);
			else if (pos.x == 0 || pos.x == game->data->max_size.x - 1
				|| pos.y == 0 || pos.y == game->data->max_size.y - 1)
				draw(game, wall, pos);
			else if (game->data->map[pos.y][pos.x] == '1')
				draw(game, desk, pos);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_elements(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->data->total)
	{
		game->data->collects[i]->img = load_image(game, "./art/collect.png");
		draw(game, game->data->collects[i]->img,
			game->data->collects[i]->pos);
		i++;
	}
	if (game->data->deathcount)
	{
		i = 0;
		while (i < game->data->deathcount)
		{
			draw_frames(game, game->data->deaths[i], 'd');
			i++;
		}
	}
	game->data->door.img_closed = load_image(game, "./art/door.png");
	game->data->door.img_open = load_image(game, "./art/door_open.png");
	draw(game, game->data->door.img_open, game->data->door.pos);
	game->data->door.img_open->enabled = false;
	draw(game, game->data->door.img_closed, game->data->door.pos);
}

void	draw_frames(t_game *game, t_actor *actor, char type)
{
	int		i;
	char	*path;
	char	*imgpath;
	char	*itxt;

	path = "./art/player/";
	if (type == 'd')
		path = "./art/death/";
	actor->imgs = malloc(actor->frames * sizeof(mlx_image_t));
	i = 0;
	while (i < actor->frames)
	{
		itxt = ft_itoa(i);
		imgpath = ft_joinstrs(3, path, itxt, ".png");
		free(itxt);
		actor->imgs[i] = load_image(game, imgpath);
		free(imgpath);
		draw(game, actor->imgs[i], actor->pos);
		actor->imgs[i]->enabled = false;
		i++;
	}
	actor->imgs[actor->currframe]->enabled = true;
}

mlx_image_t	*load_image(t_game *game, char *path)
{
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		terminate(game, "mlx", "failed to load png");
	image = mlx_texture_to_image(game->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		terminate(game, "mlx", "failed to create image");
	return (image);
}

void	draw(t_game *game, mlx_image_t *image, t_pos pos)
{
	int				check;
	int				posx;
	int				posy;

	posx = pos.x * UNIT;
	posy = pos.y * UNIT;
	check = mlx_image_to_window(game->mlx, image, posx, posy);
	if (check < 0)
		terminate(game, "mlx", "failed to put image to window");
}
