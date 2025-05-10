/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:12:14 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/10 19:07:18 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	perform_dda(t_mlx *mlx)
{
	int steps;

	steps = 0;
	while (!mlx->ray.hit && steps < MAX_DDA_STEPS)
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
	    steps++;
    }
    if (!mlx->ray.hit)
        mlx->ray.hit = 1;
}
