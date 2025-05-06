/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:49:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/05/06 18:33:04 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
