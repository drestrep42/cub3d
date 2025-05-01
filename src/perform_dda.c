/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:12:14 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/01 12:17:00 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// DDA hasta colisión con muro o fuera de mapa
void	perform_dda(t_mlx *mlx)
{
	while (!mlx->ray.hit)
	{
		if (mlx->ray.sideDistX < mlx->ray.sideDistY)
		{
			mlx->ray.sideDistX += mlx->ray.deltaDistX;
			mlx->ray.mapX += mlx->ray.stepX;
			mlx->ray.side = 0;
		}
		else
		{
			mlx->ray.sideDistY += mlx->ray.deltaDistY;
			mlx->ray.mapY += mlx->ray.stepY;
			mlx->ray.side = 1;
		}
		if (mlx->ray.mapX < 0 || mlx->ray.mapY < 0 || \
			mlx->ray.mapX >= mlx->file.map.x_nbrs || \
			mlx->ray.mapY >= mlx->file.map.y_nbrs)
		{
			mlx->ray.hit = 1;
			break ;
		}
		if (mlx->file.map.coord[mlx->ray.mapY][mlx->ray.mapX].nbr == '1')
			mlx->ray.hit = 1;
	}
}
