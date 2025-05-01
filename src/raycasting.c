/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_dda.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:51:16 by igvisera          #+#    #+#             */
/*   Updated: 2025/05/01 12:18:38 by drestrep         ###   ########.fr       */
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
	mlx->ray.mapX = (int)mlx->ray.pos_x;
	mlx->ray.mapY = (int)mlx->ray.pos_y;
	mlx->ray.deltaDistX = fabs(1.0 / mlx->ray.raydir_x);
	mlx->ray.deltaDistY = fabs(1.0 / mlx->ray.raydir_y);
	mlx->ray.hit = 0;
}

// Calcula stepX/stepY y sideDistX/sideDistY
static void	compute_step_and_side_dist(t_mlx *mlx)
{
	if (mlx->ray.raydir_x < 0)
	{
		mlx->ray.stepX = -1;
		mlx->ray.sideDistX = (mlx->ray.pos_x - mlx->ray.mapX) \
		* mlx->ray.deltaDistX;
	}
	else
	{
		mlx->ray.stepX = +1;
		mlx->ray.sideDistX = (mlx->ray.mapX + 1.0 - mlx->ray.pos_x) \
		* mlx->ray.deltaDistX;
	}
	if (mlx->ray.raydir_y < 0)
	{
		mlx->ray.stepY = -1;
		mlx->ray.sideDistY = (mlx->ray.pos_y - mlx->ray.mapY) \
		* mlx->ray.deltaDistY;
	}
	else
	{
		mlx->ray.stepY = +1;
		mlx->ray.sideDistY = (mlx->ray.mapY + 1.0 - mlx->ray.pos_y) \
		* mlx->ray.deltaDistY;
	}
}

// Calcula distancia perpendicular y límites de dibujo
void	compute_projection(t_mlx *mlx)
{
	int	proj_dist;
	int	line_height;

	if (mlx->ray.side == 0)
		mlx->ray.perpDist = ((mlx->ray.mapX - mlx->ray.pos_x) \
		+ (1 - mlx->ray.stepX) * 0.5) / mlx->ray.raydir_x;
	else
		mlx->ray.perpDist = ((mlx->ray.mapY - mlx->ray.pos_y) \
		+ (1 - mlx->ray.stepY) * 0.5) / mlx->ray.raydir_y;
	proj_dist = (mlx->width / 2.0) / tan((PI / 3.0) / 2.0);
	line_height = (int)(proj_dist / mlx->ray.perpDist);
	mlx->ray.drawStart = -line_height / 2 + mlx->height / 2;
	if (mlx->ray.drawStart < 0)
		mlx->ray.drawStart = 0;
	mlx->ray.drawEnd = line_height / 2 + mlx->height / 2;
	if (mlx->ray.drawEnd >= mlx->height)
		mlx->ray.drawEnd = mlx->height - 1;
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

// Función principal: un rayo por columna
void	cast_single_ray(t_mlx *mlx, double rayAngle, int screenX)
{
	init_ray_params(mlx, rayAngle);
	compute_step_and_side_dist(mlx);
	perform_dda(mlx);
	compute_projection(mlx);
	mlx->ray.texID = choose_texture(mlx);
	draw_stripe(mlx, screenX);
}
