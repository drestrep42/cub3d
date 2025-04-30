/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_dda.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:51:16 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/30 10:43:05 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double distance(double x, double y)
{
    return sqrt(x * x + y * y);
}

double init_distance(double x, double y, double x1, double y1, t_mlx *mlx)
{
    double delta_x;
    double delta_y;
    double angle;

    delta_x = x1 - x;
    delta_y = y1 - y;
    angle = atan2(delta_y, delta_x) - mlx->player.angle;
    return (distance(delta_x, delta_y) * cos(angle));
}

// Cálculo de la distancia al plano de proyección
static double get_proj_plane_dist(int width)
{
	const double FOV = PI / 3.0;
    return ((width / 2.0) / tan(FOV / 2.0));
}

// Inicializa posición, dirección y mapa del rayo
static void init_ray_params(t_mlx *mlx, double rayAngle)
{
    // Posición del jugador en celdas
    mlx->ray.posX = mlx->player.posX / BLOCK;
    mlx->ray.posY = mlx->player.posY / BLOCK;
    // Dirección del rayo
    mlx->ray.rayDirX = cos(rayAngle);
    mlx->ray.rayDirY = sin(rayAngle);
    // Celda actual
    mlx->ray.mapX = (int)mlx->ray.posX;
    mlx->ray.mapY = (int)mlx->ray.posY;
    // Distancias delta
    mlx->ray.deltaDistX = fabs(1.0 / mlx->ray.rayDirX);
    mlx->ray.deltaDistY = fabs(1.0 / mlx->ray.rayDirY);
    mlx->ray.hit = 0;
}

// Calcula stepX/stepY y sideDistX/sideDistY
static void compute_step_and_sideDist(t_mlx *mlx)
{
    if (mlx->ray.rayDirX < 0)
    {
        mlx->ray.stepX = -1;
        mlx->ray.sideDistX = (mlx->ray.posX - mlx->ray.mapX) * mlx->ray.deltaDistX;
    }
    else
    {
        mlx->ray.stepX = +1;
        mlx->ray.sideDistX = (mlx->ray.mapX + 1.0 - mlx->ray.posX) * mlx->ray.deltaDistX;
    }
    if (mlx->ray.rayDirY < 0)
    {
        mlx->ray.stepY = -1;
        mlx->ray.sideDistY = (mlx->ray.posY - mlx->ray.mapY) * mlx->ray.deltaDistY;
    }
    else
    {
        mlx->ray.stepY = +1;
        mlx->ray.sideDistY = (mlx->ray.mapY + 1.0 - mlx->ray.posY) * mlx->ray.deltaDistY;
    }
}

// DDA hasta colisión con muro o fuera de mapa
static void perform_dda(t_mlx *mlx)
{
    while (!mlx->ray.hit)
    {
        if (mlx->ray.sideDistX < mlx->ray.sideDistY)
        {
            mlx->ray.sideDistX += mlx->ray.deltaDistX;
            mlx->ray.mapX += mlx->ray.stepX;
            mlx->ray.side = 0;
        }
        else
        {
            mlx->ray.sideDistY += mlx->ray.deltaDistY;
            mlx->ray.mapY += mlx->ray.stepY;
            mlx->ray.side = 1;
        }
        if (mlx->ray.mapX < 0 || mlx->ray.mapY < 0 ||
            mlx->ray.mapX >= mlx->file.map.x_nbrs ||
            mlx->ray.mapY >= mlx->file.map.y_nbrs)
        {
            mlx->ray.hit = 1;
            break;
        }
        if (mlx->file.map.coord[mlx->ray.mapY][mlx->ray.mapX].nbr == '1')
            mlx->ray.hit = 1;
    }
}

// Calcula distancia perpendicular y límites de dibujo
static void compute_projection(t_mlx *mlx)
{
    if (mlx->ray.side == 0)
        mlx->ray.perpDist = ((mlx->ray.mapX - mlx->ray.posX)
            + (1 - mlx->ray.stepX) * 0.5) / mlx->ray.rayDirX;
    else
        mlx->ray.perpDist = ((mlx->ray.mapY - mlx->ray.posY)
            + (1 - mlx->ray.stepY) * 0.5) / mlx->ray.rayDirY;

    int projDist = (int)get_proj_plane_dist(mlx->width);
    int lineHeight = (int)(projDist / mlx->ray.perpDist);

    mlx->ray.drawStart = -lineHeight / 2 + mlx->height / 2;
    if (mlx->ray.drawStart < 0) mlx->ray.drawStart = 0;
    	mlx->ray.drawEnd = lineHeight / 2 + mlx->height / 2;
    if (mlx->ray.drawEnd >= mlx->height)
		mlx->ray.drawEnd = mlx->height - 1;
}

// Selecciona el ID de textura según el lado
static int choose_texture(t_mlx *mlx)
{
    if (mlx->ray.side == 0)
        return (mlx->ray.rayDirX > 0) ? SO : NO;
    else
        return (mlx->ray.rayDirY > 0) ? WE : EA;
}

// Dibuja la columna con textura o gris si no hay, manteniendo while
static void draw_stripe(t_mlx *mlx, int x)
{
    t_texture *T;   
    int y;

    T = &mlx->file.textures[mlx->ray.texID];
    if (T->empty || !T->img || !T->img->pixels)
    {
        int y = mlx->ray.drawStart;
        while (y <= mlx->ray.drawEnd)
        {
            put_pixel(x, y, 0xAAAAAA, mlx->img);
            y++;
        }
        return;
    }

    int texW;
    int texH;
    double yPos;
    uint32_t *pixels;
    mlx_texture_t *tex;
    
    tex = T->img;
    texW = tex->width;
    texH = tex->height;
    pixels = (uint32_t *)tex->pixels;

    double wallX = (mlx->ray.side == 0)
        ? (mlx->ray.posY + mlx->ray.perpDist * mlx->ray.rayDirY)
        : (mlx->ray.posX + mlx->ray.perpDist * mlx->ray.rayDirX);
    wallX -= floor(wallX);

    y = mlx->ray.drawStart;
    while (y <= mlx->ray.drawEnd)
    {
        yPos = ((double)y - mlx->ray.drawStart)
            / ((double)mlx->ray.drawEnd - mlx->ray.drawStart);
        uint32_t color = pixels[(int)(wallX * (texW - 1)) +
            (int)(yPos * (texH - 1)) * texW];
        put_pixel(x, y, color, mlx->img);
        y++;
    }
}

// Función principal: un rayo por columna
void cast_single_ray(t_mlx *mlx, double rayAngle, int screenX)
{
    init_ray_params(mlx, rayAngle);
    compute_step_and_sideDist(mlx);
    perform_dda(mlx);
    compute_projection(mlx);
    mlx->ray.texID = choose_texture(mlx);
    draw_stripe(mlx, screenX);
}
