
inspo from Julius

static void	move_vertical(t_render *game, double dir)
{
	double	movex;
	double	movey;

	movex = cos(game->player.rad) * MS * dir;
	movey = sin(game->player.rad) * MS * dir;
	if (game->map[(int)(game->player.py + movey * 1.1)][(int)(game->player.px
			+ movex * 1.1)] == '0')
	{
		game->player.px += movex;
		game->player.py += movey;
	}
}

static void	move_horizontal(t_render *game, double dir)
{
	double	movex;
	double	movey;

	movex = cos(game->player.rad + (PI * dir) / 2) * MS;
	movey = sin(game->player.rad + (PI * dir) / 2) * MS;
	if (game->map[(int)(game->player.py + movey * 1.1)][(int)(game->player.px
			+ movex * 1.1)] == '0')
	{
		game->player.px += movex;
		game->player.py += movey;
	}
}

