/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/09 18:46:28 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_alloc_and_exit(t_allocated *tobfreed, t_flag flags, \
								char *error_msg)
{
	free(tobfreed->var1);
	free(tobfreed->var2);
	if (flags.rgb_flag == true)
		free_rgb(tobfreed);
	if (flags.textures_flag == true)
		free_textures(tobfreed->mlx, 1);
	if (flags.gnl_flag == true)
		free_gnl(tobfreed->fd);
	ft_exit(error_msg);
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
