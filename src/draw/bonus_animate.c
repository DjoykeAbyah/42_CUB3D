/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus_animate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 17:08:39 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 15:31:10 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	animate_collects(t_game *game);
static void	animate_player(t_game *game);
static void	animate_death(t_game *game);

void	bonus_animate(void *param)
{
	t_game		*game;

	game = param;
	game->data->timer += 1;
	animate_collects(game);
	if (game->data->deathcount)
		animate_death(game);
	animate_player(game);
}

static void	animate_death(t_game *game)
{
	int			i;
	t_actor		*death;

	if (game->data->timer % game->data->speed == 0)
	{
		i = 0;
		while (i < game->data->deathcount)
		{
			death = game->data->deaths[i];
			death->imgs[death->currframe]->enabled = false;
			death->currframe += 1;
			if (death->currframe == death->frames)
				death->currframe = 0;
			if (game->data->condition != 'w')
			{
				death->imgs[death->currframe]->instances[0].x
					= death->pos.x * UNIT;
				death->imgs[death->currframe]->instances[0].y
					= death->pos.y * UNIT;
				death->imgs[death->currframe]->enabled = true;
			}
			i++;
		}
	}
}

static void	animate_player(t_game *game)
{
	t_pos		p_pos;
	t_actor		*player;

	if (game->data->timer % game->data->speed == 0)
	{
		player = &game->data->player;
		p_pos = player->pos;
		player->imgs[player->currframe]->enabled = false;
		player->currframe += 1;
		if (player->currframe == player->frames)
			player->currframe = 0;
		if (!game->data->condition)
		{
			player->imgs[player->currframe]->instances[0].x = p_pos.x * UNIT;
			player->imgs[player->currframe]->instances[0].y = p_pos.y * UNIT;
			player->imgs[player->currframe]->enabled = true;
		}
	}
}

static void	animate_collects(t_game *game)
{
	int			i;
	static int	move = 1;

	if (game->data->timer % game->data->speed == 0)
	{
		if (move > 0)
			move += 2;
		else
			move -= 2;
		if (move == 7)
			move = -1;
		else if (move == -5)
			move = 1;
		i = 0;
		while (i < game->data->total)
		{
			game->data->collects[i]->img->instances[0].y
				= (game->data->collects[i]->pos.y * UNIT) + move;
			i++;
		}
	}
}
