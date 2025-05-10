/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:12:14 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/10 20:29:42 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	dist_calc(t_mlx *mlx)
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
}

void	perform_dda(t_mlx *mlx)
{
	int	steps;

	steps = 0;
	while (!mlx->ray.hit && steps < MAX_DDA_STEPS)
	{
		dist_calc(mlx);
		if (mlx->ray.map_x < 0 || mlx->ray.map_y < 0 || \
			mlx->ray.map_x >= mlx->file.map.x_nbrs || \
			mlx->ray.map_y >= mlx->file.map.y_nbrs)
		{
			mlx->ray.hit = 1;
			break ;
		}
		if (mlx->file.map.coord[mlx->ray.map_y][mlx->ray.map_x].nbr == '1')
			mlx->ray.hit = 1;
		steps++;
	}
	if (!mlx->ray.hit)
		mlx->ray.hit = 1;
}
