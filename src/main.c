/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 12:14:12 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/21 15:26:00 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub3d(t_cub3d *cub3d);
static void	clear_cub3d(t_cub3d *cub3d);

int	main(int argc, char *argv[])
{
	char		*filename;
	char		*filetype;
	t_cub3d		cub3d;

	if (argc > 1)
	{
		filename = argv[1];
		filetype = ft_strrchr(filename, '.');
		if (ft_strncmp(".cub", filetype, 5) == 0)
		{
			init_cub3d(&cub3d);
			map(&cub3d, filename);
			//game_start(&cub3d);
			terminate(&cub3d, NULL, NULL);
		}
	}
	terminate(NULL, "user error", "bad input");
}

void	terminate(t_cub3d *cub3d, char *what, char *why)
{
	if (cub3d)
	{
		// mlx_terminate(cub3d->mlx);
		clear_cub3d(cub3d);
	}
	if (!what && !why)
		exit(EXIT_SUCCESS);
	ft_perror("ERROR", what, why);
	exit(EXIT_FAILURE);
}

static void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->map.data = NULL;
	cub3d->mlx = NULL;
}

static void	clear_cub3d(t_cub3d *cub3d)
{
	ft_free_strarr(cub3d->map.data);
}
