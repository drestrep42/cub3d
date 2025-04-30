/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:49:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/30 18:23:10 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//colision de pared
bool   touch(double px, double py, t_map *map, double radius)
{
    int    minX = (int)((px - radius) / BLOCK);
    int    maxX = (int)((px + radius) / BLOCK);
    int    minY = (int)((py - radius) / BLOCK);
    int    maxY = (int)((py + radius) / BLOCK);
    int    y, x;

    // si nos salimos del mapa (incluso con radio), hacemos colisión
    if (minX < 0 || minY < 0 || maxX >= map->x_nbrs || maxY >= map->y_nbrs)
        return true;

    // por cada celda potencialmente en contacto…
    for (y = minY; y <= maxY; y++)
    {
        for (x = minX; x <= maxX; x++)
        {
            if (map->coord[y][x].nbr == '1')
            {
                // Encuentro el punto más cercano de la celda al jugador
                double nearestX = fmax(x*BLOCK, fmin(px, x*BLOCK + BLOCK));
                double nearestY = fmax(y*BLOCK, fmin(py, y*BLOCK + BLOCK));
                double dx = px - nearestX;
                double dy = py - nearestY;
                if (dx*dx + dy*dy < radius*radius)
                    return true;
            }
        }
    }
    return false;
}
