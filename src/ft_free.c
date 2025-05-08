/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/08 16:48:02 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_allocated_and_exit(t_allocated *tobfreed, bool rgb_flag, \
								bool textures_flag, char *error_msg)
{
	free(tobfreed->var1);
	free(tobfreed->var2);
	if (rgb_flag == true)
	{
		free(tobfreed->var3[0]);
		free(tobfreed->var3[1]);
		free(tobfreed->var3[2]);
		free(tobfreed->var3);
	}
	if (textures_flag == true)
		free_textures(tobfreed->mlx, 1);
	ft_exit(error_msg);
}

void	free_textures(t_mlx *mlx, int path_flag)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (mlx->file.textures[i].xpm)
		{
			if (path_flag == 1)
				free(mlx->file.textures[i].path);
			mlx_delete_texture(&mlx->file.textures[i].xpm->texture);
			mlx->file.textures[i].xpm = NULL;
		}
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->coord[i])
		free(map->coord[i++]);
	free(map->coord);
	i = 0;
	while (map->raw_lines[i])
		free(map->raw_lines[i++]);
	free(map->raw_lines);
}

void	free_all(t_mlx *mlx, int path_flag)
{
	free_map(&mlx->file.map);
	free_textures(mlx, path_flag);
}
