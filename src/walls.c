/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:49:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/30 22:07:05 by drestrep         ###   ########.fr       */
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

//colision de pared
bool	touch(double px, double py, t_map *map, double radius)
{
	t_touch	touch;

	touch.px = px;
	touch.py = py;
	touch.min_x = (int)((px - radius) / BLOCK);
	touch.min_y = (int)((py - radius) / BLOCK);
	touch.max_x = (int)((px + radius) / BLOCK);
	touch.max_y = (int)((py + radius) / BLOCK);
	if (touch.min_x < 0 || touch.min_y < 0 || \
		touch.max_x >= map->x_nbrs || touch.max_y >= map->y_nbrs)
		return (true);
	touch.y = touch.min_y;
	if (touch_loop(map, touch, radius) == true)
		return (true);
	return (false);
}
