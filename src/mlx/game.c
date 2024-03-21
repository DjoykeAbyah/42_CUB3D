/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 14:36:46 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 19:17:22 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	collect(t_game *game);

void	game_start(t_data *data)
{
	t_game	game;

	game.data = data;
	game.mlx = mlx_init(ft_biggest(game.data->max_size.x * UNIT, 512),
			(game.data->max_size.y * UNIT) + (UNIT * 2), "so_long", false);
	if (!game.mlx)
		terminate(NULL, "mlx", "failed to init");
	bonus_draw_text(&game, "Complete evals and avoid the deadline!", 0);
	draw_map(&game);
	draw_elements(&game);
	draw_frames(&game, &game.data->player, 'p');
	mlx_key_hook(game.mlx, input_handler, &game);
	mlx_loop_hook(game.mlx, bonus_animate, &game);
	mlx_loop(game.mlx);
}

void	game_move_player(t_game *game, int x, int y)
{
	game->data->moves += 1;
	bonus_draw_text(game, NULL, game->data->moves);
	game->data->player.pos.x = x;
	game->data->player.pos.y = y;
	if (game->data->map[y][x] == 'C')
	{
		game->data->map[y][x] = '0';
		collect(game);
	}
	else if (game->data->map[y][x] == 'E'
		&& game->data->score == game->data->total)
	{
		bonus_draw_text(game, "Well done!", game->data->moves);
		game->data->condition = 'w';
	}
}

static void	collect(t_game *game)
{
	t_pos	p_pos;
	int		i;

	p_pos = game->data->player.pos;
	game->data->score += 1;
	i = 0;
	while (i < game->data->total)
	{
		if (game->data->collects[i]->pos.x == p_pos.x
			&& game->data->collects[i]->pos.y == p_pos.y)
		{
			game->data->collects[i]->img->enabled = false;
			break ;
		}
		i++;
	}
	if (game->data->score == game->data->total)
	{
		bonus_draw_text(game, "ALL EVALS DONE! Time to go!",
			game->data->moves);
		game->data->door.img_closed->enabled = false;
		game->data->door.img_open->enabled = true;
	}
}
