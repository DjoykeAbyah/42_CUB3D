/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inputs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 12:19:45 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 19:25:54 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_player_movement(t_game *game, mlx_key_data_t keydata);
static void	handle_death_movement(t_game *game, mlx_key_data_t keydata);

void	input_handler(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		terminate(game, NULL, NULL);
	if (!game->data->condition)
	{
		handle_player_movement(game, keydata);
		if (game->data->deathcount)
			handle_death_movement(game, keydata);
	}
}

static void	handle_player_movement(t_game *game, mlx_key_data_t keydata)
{
	t_pos	p_pos;

	p_pos = game->data->player.pos;
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		&& keydata.action == MLX_RELEASE
		&& game->data->map[p_pos.y - 1][p_pos.x] != '1')
		game_move_player(game, p_pos.x, p_pos.y - 1);
	else if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		&& keydata.action == MLX_RELEASE
		&& game->data->map[p_pos.y + 1][p_pos.x] != '1')
		game_move_player(game, p_pos.x, p_pos.y + 1);
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		&& keydata.action == MLX_RELEASE
		&& game->data->map[p_pos.y][p_pos.x - 1] != '1')
		game_move_player(game, p_pos.x - 1, p_pos.y);
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		&& keydata.action == MLX_RELEASE
		&& game->data->map[p_pos.y][p_pos.x + 1] != '1')
		game_move_player(game, p_pos.x + 1, p_pos.y);
}

static void	handle_death_movement(t_game *game, mlx_key_data_t keydata)
{
	static int	turn;
	int			i;

	if (keydata.action == MLX_RELEASE
		&& (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A
			|| keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S
			|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D))
	{
		turn += 1;
		if (turn % 2 == 0)
		{
			i = 0;
			while (i < game->data->deathcount)
			{
				bonus_move_death(game, i);
				if (game->data->deaths[i]->pos.x == game->data->player.pos.x
					&& game->data->deaths[i]->pos.y == game->data->player.pos.y)
					bonus_game_over(game);
				i++;
			}
		}
	}
}
