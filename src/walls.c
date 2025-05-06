/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:49:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/05/06 18:26:36 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	touch_loop(t_map *map, t_touch touch, double radius)
{
	while (touch.y <= touch.min_y)
	{
		touch.x = touch.min_x;
		while (touch.x <= touch.max_x)
		{
			if (map->coord[touch.y][touch.x].nbr == '1')
			{
				touch.nearest_x = fmax(touch.x * BLOCK, \
				fmin(touch.px, touch.x * BLOCK + BLOCK));
				touch.nearest_y = fmax(touch.y * BLOCK, \
				fmin(touch.py, touch.y * BLOCK + BLOCK));
				touch.dx = touch.px - touch.nearest_x;
				touch.dy = touch.py - touch.nearest_y;
				if (touch.dx * touch.dx + touch.dy * touch.dy < radius * radius)
					return (true);
			}
			touch.x++;
		}
		touch.y++;
	}
	return (false);
}

bool	touch(double px, double py, t_map *map)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (x < 0 || y < 0 || x >= map->x_nbrs || y >= map->y_nbrs)
		return (true);
	if (map->coord[y][x].nbr == '1')
		return (true);
	return (false);
}
