/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:16:49 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/10 21:06:25 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	calc_dh(t_mlx *mlx, t_dh dh_struct)
{
	int	tex_y;
	int	tex_x;
	int	dh;

	dh = mlx->ray.draw_end - mlx->ray.draw_start;
	if (dh <= 0)
	{
		tex_y = (dh_struct.t->img->height - 1) / 2;
		tex_x = (int)(dh_struct.wall_x * (dh_struct.t->img->width - 1));
		dh_struct.color = dh_struct.pixels[tex_x + \
		tex_y * dh_struct.t->img->width];
		put_pixel(dh_struct.x, dh_struct.y, dh_struct.color, mlx->img);
		return (-1);
	}
	return (dh);
}

double	get_pos_y(t_mlx *mlx, int dh, int y)
{
	double	pos_y;

	if (mlx->ray.line_height <= HEIGHT)
		pos_y = ((double)y - mlx->ray.draw_start)
			/ ((double)dh);
	else
		pos_y = (((double)(mlx->ray.line_height - HEIGHT) / 2.0) + \
		(y - mlx->ray.draw_start)) / (double)mlx->ray.line_height;
	return (pos_y);
}

void	draw_textured_column(t_mlx *mlx, t_texture *t, double wall_x, int x)
{
	t_dh	dh_struct;
	double	pos_y;
	int		tex_y;
	int		tex_x;

	dh_struct.pixels = (uint32_t *)t->img->pixels;
	dh_struct.y = mlx->ray.draw_start;
	dh_struct.wall_x = wall_x;
	dh_struct.x = x;
	dh_struct.t = t;
	dh_struct.dh = calc_dh(mlx, dh_struct);
	if (dh_struct.dh == -1)
		return ;
	while (dh_struct.y <= mlx->ray.draw_end)
	{
		pos_y = get_pos_y(mlx, dh_struct.dh, dh_struct.y);
		tex_y = (int)(pos_y * (t->img->height - 1));
		tex_x = (int)(wall_x * (t->img->width - 1));
		dh_struct.color = dh_struct.pixels[tex_x + tex_y * t->img->width];
		put_pixel(x, dh_struct.y, dh_struct.color, mlx->img);
		dh_struct.y++;
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
