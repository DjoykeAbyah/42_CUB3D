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
			ft_bzero(&cub3d, sizeof(cub3d));
			parse_map(&cub3d.mapdata, filename);
			start_cub3d(&cub3d);
			terminate(&cub3d, NULL, NULL);
		}
	}
	terminate(NULL, "user error", "bad input");
}

void	terminate(t_cub3d *cub3d, const char *what, const char *why)
{
	if (cub3d)
	{
		clear_map(&cub3d->mapdata);
		mlx_close_window(cub3d->mlx);
		mlx_terminate(cub3d->mlx);
	}
	if (!what && !why)
		exit(EXIT_SUCCESS);
	ft_perror("ERROR", what, why);
	exit(EXIT_FAILURE);
}
