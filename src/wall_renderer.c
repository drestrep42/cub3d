/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:16:49 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/09 13:19:49 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_textured_column(t_mlx *mlx, t_texture *t, double wall_x, int x)
{
	uint32_t		*pixels;
	uint32_t		color;
	double			pos_y;
	int				y;

	y = mlx->ray.draw_start;
	pixels = (uint32_t *)t->img->pixels;
	while (y <= mlx->ray.draw_end)
	{
		if (mlx->ray.line_height <= HEIGHT)
			pos_y = ((double)y - mlx->ray.draw_start) / \
			((double)mlx->ray.draw_end - mlx->ray.draw_start);
		else
			pos_y = (double)(((mlx->ray.line_height - HEIGHT) / 2.0) + y) / \
			(double)mlx->ray.line_height;
		color = pixels[(int)(wall_x * (t->img->width - 1)) + (int)(pos_y * \
		(t->img->height - 1)) *t->img->width];
		put_pixel(x, y, color, mlx->img);
		y++;
	}
}

void	draw_stripe(t_mlx *mlx, int x)
{
	t_texture		*t;
	double			wall_x;

	t = &mlx->file.textures[mlx->ray.tex_id];
	if (t->empty || !t->img || !t->img->pixels)
	{
		while (mlx->ray.draw_start <= mlx->ray.draw_end)
		{
			put_pixel(x, mlx->ray.draw_start, 0xAAAAAA, mlx->img);
			mlx->ray.draw_start++;
		}
		return ;
	}
	if (mlx->ray.side == 0)
		wall_x = mlx->ray.pos_y + mlx->ray.perp_dist * mlx->ray.raydir_y;
	else
		wall_x = mlx->ray.pos_x + mlx->ray.perp_dist * mlx->ray.raydir_x;
	wall_x -= floor(wall_x);
	draw_textured_column(mlx, t, wall_x, x);
}
