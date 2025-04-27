/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:49:59 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/27 17:50:48 by igvisera         ###   ########.fr       */
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

bool touch(double px, double py, t_map *map)
{
    int x;
    int y;

    x = (int)(px / BLOCK);
    y = (int)(py / BLOCK);
    if (x < 0 || y < 0 || x >= map->x_nbrs || y >= map->y_nbrs)
        return true;
    if (map->coord[y][x].nbr == '1')
        return true;
    return false;
}