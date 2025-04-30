/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/30 17:55:44 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	free_all(t_mlx *mlx)
{
	free(mlx->file.textures[NO].path);
	free(mlx->file.textures[SO].path);
	free(mlx->file.textures[EA].path);
	free(mlx->file.textures[WE].path);
	free_map(&mlx->file.map);
}
