/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:47:58 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/27 17:49:35 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void put_pixel(int x, int y, uint32_t color, mlx_image_t *img)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
    {
        return;
    }
    uint32_t color_swapped;
    int i;

    color_swapped = 0;
    i = 0;
    while (i < 4)
    {
        color_swapped <<= 8;
        color_swapped |= (0xff & color);
        color >>= 8;
        i++;
    }
    mlx_put_pixel(img, x, y, color_swapped | 0xff);
}

void clear_image(t_mlx *mlx)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            put_pixel(x, y, 0, mlx->img);
            x++;
        }
        y++;
    }
}

int	get_color(t_mlx *mlx, int mode)
{

    if (mode == 1)
        return ((mlx->file.ceiling.color[R] | 
            ((mlx->file.ceiling.color[G] & 0xFF) << 8) | 
            ((mlx->file.ceiling.color[B] & 0xFF) << 16) | 
            (0xFF << 24)));
    else
        return ((mlx->file.floor.color[R] | 
            ((mlx->file.floor.color[G] & 0xFF) << 8) | 
            ((mlx->file.floor.color[B] & 0xFF) << 16) | 
            (0xFF << 24)));
}

void print_sky_and_floor(t_mlx *mlx)
{
    int y = -1;
    while (++y < HEIGHT / 2)
    {
        int x = -1;
        while (++x < WIDTH)
            put_pixel(x, y, get_color(mlx, 1), mlx->img);
    }
    y = (HEIGHT / 2) - 1;
    while (++y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
        {
            put_pixel(x, y, get_color(mlx, 0), mlx->img);
            x++;
        }
    }
}