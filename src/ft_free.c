/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/27 17:47:57 by drestrep         ###   ########.fr       */
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
}

void	free_all(t_mlx *mlx)
{
	free(mlx->file.textures[NO].path);
	free(mlx->file.textures[SO].path);
	free(mlx->file.textures[EA].path);
	free(mlx->file.textures[WE].path);
	free_map(&mlx->file.map);
}
