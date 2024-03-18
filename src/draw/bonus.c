/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bonus.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 13:11:16 by dliu          #+#    #+#                 */
/*   Updated: 2023/03/02 13:11:45 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	bonus_draw_text(t_game *game, char *text, int moves)
{
	t_pos	txtpos;
	t_pos	mvpos;
	char	*mtxt;

	txtpos.y = ((game->data->max_size.y * UNIT) + (0.5 * UNIT));
	mvpos.x = 2 * UNIT;
	mvpos.y = ((game->data->max_size.y * UNIT) + (UNIT));
	if (text)
	{
		if (game->data->text.text)
			mlx_delete_image(game->mlx, game->data->text.text);
		game->data->text.text = mlx_put_string(game->mlx, text, UNIT, txtpos.y);
	}
	if (!game->data->text.moves)
		mlx_put_string(game->mlx, "Moves: ", UNIT, mvpos.y);
	else
		mlx_delete_image(game->mlx, game->data->text.moves);
	mtxt = ft_itoa(moves);
	game->data->text.moves = mlx_put_string(game->mlx, mtxt,
			mvpos.x, mvpos.y);
	free(mtxt);
}

void	bonus_add_death(t_data *data, int x, int y)
{
	t_actor	**deaths;
	int		i;

	deaths = malloc((data->deathcount + 1) * sizeof(*deaths));
	if (!deaths)
		terminate(NULL, "malloc", strerror(errno));
	i = 0;
	while (data->deaths && i < data->deathcount)
	{
		deaths[i] = data->deaths[i];
		i++;
	}
	deaths[i] = malloc(sizeof (**deaths));
	free(data->deaths);
	if (!deaths[i])
		terminate(NULL, "malloc", strerror(errno));
	deaths[i]->pos.x = x;
	deaths[i]->pos.y = y;
	deaths[i]->frames = 5;
	deaths[i]->currframe = 0;
	data->map[y][x] = '0';
	data->deaths = deaths;
	data->deathcount += 1;
}

static int	crowded(t_game *game, int x, int y)
{
	int		i;

	i = 0;
	while (i < game->data->deathcount)
	{
		if (game->data->deaths[i]->pos.x == x
			&& game->data->deaths[i]->pos.y == y)
			return (1);
		i++;
	}
	return (0);
}

void	bonus_move_death(t_game *game, int i)
{
	t_pos	d_pos;
	t_pos	p_pos;

	d_pos = game->data->deaths[i]->pos;
	p_pos = game->data->player.pos;
	if (d_pos.x < p_pos.x && !crowded(game, d_pos.x + 1, d_pos.y))
		game->data->deaths[i]->pos.x += 1;
	else if (d_pos.x > p_pos.x && !crowded(game, d_pos.x - 1, d_pos.y))
		game->data->deaths[i]->pos.x -= 1;
	d_pos = game->data->deaths[i]->pos;
	if (d_pos.y < p_pos.y && !crowded(game, d_pos.x, d_pos.y + 1))
		game->data->deaths[i]->pos.y += 1;
	else if (d_pos.y > p_pos.y && !crowded(game, d_pos.x, d_pos.y - 1))
		game->data->deaths[i]->pos.y -= 1;
}

void	bonus_game_over(t_game *game)
{
	game->data->condition = 'l';
	bonus_draw_text(game, "Death comes for us all...", game->data->moves);
}
