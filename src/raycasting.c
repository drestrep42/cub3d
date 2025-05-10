/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:51:16 by igvisera          #+#    #+#             */
/*   Updated: 2025/05/10 19:08:19 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Inicializa posición, dirección y mapa del rayo
static void	init_ray_params(t_mlx *mlx, double rayAngle)
{
	mlx->ray.pos_x = mlx->player.pos_x / BLOCK;
	mlx->ray.pos_y = mlx->player.pos_y / BLOCK;
	mlx->ray.raydir_x = cos(rayAngle);
	mlx->ray.raydir_y = sin(rayAngle);
	mlx->ray.map_x = (int)mlx->ray.pos_x;
	mlx->ray.map_y = (int)mlx->ray.pos_y;
	mlx->ray.delta_dist_x = fabs(1.0 / mlx->ray.raydir_x);
	mlx->ray.delta_dist_y = fabs(1.0 / mlx->ray.raydir_y);
	mlx->ray.hit = 0;
}

// Calcula step_x/step_y y side_dist_x/side_dist_y
static void	compute_step_and_side_dist(t_mlx *mlx)
{
	if (mlx->ray.raydir_x < 0)
	{
		mlx->ray.step_x = -1;
		mlx->ray.side_dist_x = (mlx->ray.pos_x - mlx->ray.map_x) \
		* mlx->ray.delta_dist_x;
	}
	else
	{
		mlx->ray.step_x = +1;
		mlx->ray.side_dist_x = (mlx->ray.map_x + 1.0 - mlx->ray.pos_x) \
		* mlx->ray.delta_dist_x;
	}
	if (mlx->ray.raydir_y < 0)
	{
		mlx->ray.step_y = -1;
		mlx->ray.side_dist_y = (mlx->ray.pos_y - mlx->ray.map_y) \
		* mlx->ray.delta_dist_y;
	}
	else
	{
		mlx->ray.step_y = +1;
		mlx->ray.side_dist_y = (mlx->ray.map_y + 1.0 - mlx->ray.pos_y) \
		* mlx->ray.delta_dist_y;
	}
}

static double safe_div(double num, double den)
{
    const double EPS = 1e-6;
    if (fabs(den) < EPS)
        return num / (den < 0 ? -EPS : EPS);
    return num / den;
}

// Calcula distancia perpendicular y límites de dibujo
static void compute_projection(t_mlx *mlx)
{
    int proj_dist;

    if (mlx->ray.side == 0)
        mlx->ray.perp_dist = safe_div(
            (mlx->ray.map_x - mlx->ray.pos_x + (1 - mlx->ray.step_x) * 0.5),
            mlx->ray.raydir_x
        );
    else
        mlx->ray.perp_dist = safe_div(
            (mlx->ray.map_y - mlx->ray.pos_y + (1 - mlx->ray.step_y) * 0.5),
            mlx->ray.raydir_y
        );
    proj_dist = (mlx->width / 2.0) / tan((PI / 3.0) / 2.0);
    mlx->ray.line_height = (int)(proj_dist / mlx->ray.perp_dist);
    mlx->ray.draw_start = -mlx->ray.line_height / 2 + mlx->height / 2;
    if (mlx->ray.draw_start < 0)
		mlx->ray.draw_start = 0;
	mlx->ray.draw_end = mlx->ray.line_height / 2 + mlx->height / 2;
    if (mlx->ray.draw_end >= mlx->height)
		mlx->ray.draw_end = mlx->height - 1;
}

// Selecciona el ID de textura según el lado
static int	choose_texture(t_mlx *mlx)
{
	if (mlx->ray.side == 0)
	{
		if (mlx->ray.raydir_x > 0)
			return (SO);
		return (NO);
	}
	else
	{
		if (mlx->ray.raydir_y > 0)
			return (WE);
		return (EA);
	}
}

void	cast_single_ray(t_mlx *mlx, double rayAngle, int screenX)
{
	init_ray_params(mlx, rayAngle);
	compute_step_and_side_dist(mlx);
	perform_dda(mlx);
	compute_projection(mlx);
	mlx->ray.tex_id = choose_texture(mlx);
	draw_stripe(mlx, screenX);
}
