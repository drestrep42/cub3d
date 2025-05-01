/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:57:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/01 11:15:30 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_textures(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (mlx->file.textures[i].xpm)
		{
			mlx_delete_texture(&mlx->file.textures[i].xpm->texture);
			mlx->file.textures[i].xpm = NULL;
		}
	}
}

int	main(int ac, char **argv)
{
	t_mlx	mlx;

	mlx_set_setting(MLX_MAXIMIZED, false);
	if (ac != 2 || ft_memcmp(argv[1], "", 1) == 0)
		ft_exit(USAGE_ERROR);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		ft_exit(USAGE_ERROR);
	file_init(&mlx.file);
	parsing(&mlx, argv[1]);
	cube_init(&mlx);
	free_all(&mlx);
	free_textures(&mlx);
	return (0);
}
