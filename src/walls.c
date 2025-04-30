/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:49:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/30 10:51:12 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_square(int x, int y, int size, uint32_t color, mlx_image_t *img)
{
    int i;

    i = 0;
    while (i < size)
        put_pixel(x + i++, y, color, img);
    i = 0;
    while (i < size)
        put_pixel(x, y + i++, color, img);
    i = 0;
    while (i < size)
        put_pixel(x + size, y + i++, color, img);
    i = 0;
    while (i < size)
        put_pixel(x + i++, y + size, color, img);
}

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
