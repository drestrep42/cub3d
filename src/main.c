/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:57:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/27 12:48:54 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **argv)
{
	t_mlx	mlx;

	mlx_set_setting(MLX_MAXIMIZED, false);
	if (ac != 2 || ft_memcmp(argv[1], "", 1) == 0)
		ft_exit(USAGE_ERROR);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		ft_exit(USAGE_ERROR);
	file_init(&mlx.file);
	parsing(&mlx.file, argv[1]);
	cube_init(&mlx);
	mlx_loop(mlx.mlx_ptr);
	free_all(&mlx);
	return (0);
}
