/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:12:14 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/09 13:56:34 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	perform_dda(t_mlx *mlx)
{
	while (!mlx->ray.hit)
	{
		if (mlx->ray.side_dist_x < mlx->ray.side_dist_y)
		{
			mlx->ray.side_dist_x += mlx->ray.delta_dist_x;
			mlx->ray.map_x += mlx->ray.step_x;
			mlx->ray.side = 0;
		}
		else
		{
			mlx->ray.side_dist_y += mlx->ray.delta_dist_y;
			mlx->ray.map_y += mlx->ray.step_y;
			mlx->ray.side = 1;
		}
		if (mlx->ray.map_x < 0 || mlx->ray.map_y < 0 || \
			mlx->ray.map_x >= mlx->file.map.x_nbrs || \
			mlx->ray.map_y >= mlx->file.map.y_nbrs)
		{
			mlx->ray.hit = 1;
			break ;
		}
		if (mlx->file.map.coord[mlx->ray.map_y][mlx->ray.map_x].nbr == '1')
			mlx->ray.hit = 1;
	}
}
