/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:16:49 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/01 12:18:52 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_textured_column(t_mlx *mlx, t_texture *t, double wall_x, int x)
{
	uint32_t		*pixels;
	uint32_t		color;
	double			pos_y;
	int				y;

	y = mlx->ray.drawStart;
	pixels = (uint32_t *)t->img->pixels;
	while (y <= mlx->ray.drawEnd)
	{
		pos_y = ((double)y - mlx->ray.drawStart) \
			/ ((double)mlx->ray.drawEnd - mlx->ray.drawStart);
		color = pixels[(int)(wall_x * (t->img->width - 1)) + \
			(int)(pos_y * (t->img->height - 1)) *t->img->width];
		put_pixel(x, y, color, mlx->img);
		y++;
	}
}

// Dibuja la columna con textura o gris si no hay, manteniendo while
void	draw_stripe(t_mlx *mlx, int x)
{
	t_texture		*t;
	double			wall_x;

	t = &mlx->file.textures[mlx->ray.texID];
	if (t->empty || !t->img || !t->img->pixels)
	{
		while (mlx->ray.drawStart <= mlx->ray.drawEnd)
		{
			put_pixel(x, mlx->ray.drawStart, 0xAAAAAA, mlx->img);
			mlx->ray.drawStart++;
		}
		return ;
	}
	if (mlx->ray.side == 0)
		wall_x = mlx->ray.pos_y + mlx->ray.perpDist * mlx->ray.raydir_y;
	else
		wall_x = mlx->ray.pos_x + mlx->ray.perpDist * mlx->ray.raydir_x;
	wall_x -= floor(wall_x);
	draw_textured_column(mlx, t, wall_x, x);
}
