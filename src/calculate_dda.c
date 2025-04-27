/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_dda.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:51:16 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/27 19:32:48 by igvisera         ###   ########.fr       */
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

// void cast_single_ray(t_mlx *mlx, double rayAngle, int screenX)
// {
//     // 1) Parámetros de cámara
//     const double FOV = PI / 3.0;
//     const double projPlaneDist = (WIDTH / 2.0) / tan(FOV / 2.0);

//     // 2) Posición del jugador en unidades de celda
//     double posX = mlx->player.posX / BLOCK;
//     double posY = mlx->player.posY / BLOCK;

//     // 3) Dirección del rayo
//     double rayDirX = cos(rayAngle);
//     double rayDirY = sin(rayAngle);

//     // 4) Celda inicial
//     int mapX = (int)posX;
//     int mapY = (int)posY;

//     // 5) Distancias delta
//     double deltaDistX = fabs(1.0 / rayDirX);
//     double deltaDistY = fabs(1.0 / rayDirY);

//     // 6) Cálculo de step y sideDist
//     int stepX, stepY;
//     double sideDistX, sideDistY;
//     if (rayDirX < 0)
//     {
//         stepX     = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//     } else
//     {
//         stepX     = +1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//     }
//     if (rayDirY < 0)
//     {
//         stepY     = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//     } else
//     {
//         stepY     = +1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//     }

//     // 7) DDA: avanzamos hasta chocar con '1'
//     int hit = 0, side;
//     while (!hit)
//     {
//         if (sideDistX < sideDistY)
//         {
//             sideDistX += deltaDistX;
//             mapX      += stepX;
//             side       = 0;
//         } else
//         {
//             sideDistY += deltaDistY;
//             mapY      += stepY;
//             side       = 1;
//         }
//         // fuera de mapa?
//         if (mapX < 0 || mapY < 0 ||
//             mapX >= mlx->file.map.x_nbrs ||
//             mapY >= mlx->file.map.y_nbrs)
//         {
//             hit = 1;
//             break;
//         }
//         if (mlx->file.map.coord[mapY][mapX].nbr == '1')
//             hit = 1;
//     }

//     // 8) Distancia perpendicular (en celdas)
//     double perpDist = (side == 0)
//         ? ((mapX - posX) + (1 - stepX) * 0.5) / rayDirX
//         : ((mapY - posY) + (1 - stepY) * 0.5) / rayDirY;

//     // 9) Altura de la línea (en píxeles)
//     int lineHeight = (int)(projPlaneDist / perpDist);

//     // 10) Límite superior/inferior de la línea
//     int drawStart = -lineHeight / 2 + HEIGHT / 2;
//     if (drawStart < 0) drawStart = 0;
//     int drawEnd = lineHeight / 2 + HEIGHT / 2;
//     if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

//     // 11) Seleccionamos la textura correcta
//     int texID;
//     if (side == 0)
//         texID = (rayDirX > 0) ? SO : NO;
//     else
//         texID = (rayDirY > 0) ? WE : EA;
//     t_texture *T = &mlx->file.textures[texID];

//     // 12) Si no hay textura (o puntero nulo), dibujamos gris
//     if (T->empty || T->img == NULL || T->img->pixels == NULL) {
//         for (int y = drawStart; y <= drawEnd; y++)
//             put_pixel(screenX, y, 0xAAAAAA, mlx->img);
//         return;
//     }

//     // 13) Muestreamos la textura
//     mlx_texture_t *tex   = T->img;
//     int texW  = tex->width;
//     int texH  = tex->height;
//     uint32_t *pixels = (uint32_t *)tex->pixels;

//     // 13a) Cálculo de wallX (0.0–1.0)
//     double x_pos = (side == 0)
//         ? (posY + perpDist * rayDirY)
//         : (posX + perpDist * rayDirX);
//     x_pos -= floor(x_pos);

//     // 13d) bucle de pintado
//     int y = drawStart;
//     double y_pos;
//     uint32_t color;
//     while (y <= drawEnd)
//     {
//         y_pos = ((double)y - drawStart) / ((double)drawEnd - drawStart);
//         if (y_pos < 0 || y_pos > 1)
//             ft_exit("y_pos out range");
//         if (x_pos < 0 || x_pos > 1)
//             ft_exit("x_pos out range");
//         color = pixels[(int)floor(x_pos * (texW - 1)) + (int)floor(y_pos * (texH - 1)) * texW];
//         put_pixel(screenX, y, color, mlx->img);
//         y++;
//     }
// }


// Cálculo de la distancia al plano de proyección
static double get_proj_plane_dist(int width)
{
	const double FOV = PI / 3.0;
    return (width / 2.0) / tan(FOV / 2.0);
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
    if (mlx->ray.rayDirX < 0) {
        mlx->ray.stepX = -1;
        mlx->ray.sideDistX = (mlx->ray.posX - mlx->ray.mapX) * mlx->ray.deltaDistX;
    } else {
        mlx->ray.stepX = +1;
        mlx->ray.sideDistX = (mlx->ray.mapX + 1.0 - mlx->ray.posX) * mlx->ray.deltaDistX;
    }
    if (mlx->ray.rayDirY < 0) {
        mlx->ray.stepY = -1;
        mlx->ray.sideDistY = (mlx->ray.posY - mlx->ray.mapY) * mlx->ray.deltaDistY;
    } else {
        mlx->ray.stepY = +1;
        mlx->ray.sideDistY = (mlx->ray.mapY + 1.0 - mlx->ray.posY) * mlx->ray.deltaDistY;
    }
}

// DDA hasta colisión con muro o fuera de mapa
static void perform_dda(t_mlx *mlx)
{
    while (!mlx->ray.hit) {
        if (mlx->ray.sideDistX < mlx->ray.sideDistY) {
            mlx->ray.sideDistX += mlx->ray.deltaDistX;
            mlx->ray.mapX += mlx->ray.stepX;
            mlx->ray.side = 0;
        } else {
            mlx->ray.sideDistY += mlx->ray.deltaDistY;
            mlx->ray.mapY += mlx->ray.stepY;
            mlx->ray.side = 1;
        }
        if (mlx->ray.mapX < 0 || mlx->ray.mapY < 0 ||
            mlx->ray.mapX >= mlx->file.map.x_nbrs ||
            mlx->ray.mapY >= mlx->file.map.y_nbrs) {
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
    if (mlx->ray.drawEnd >= mlx->height) mlx->ray.drawEnd = mlx->height - 1;
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
    t_texture *T = &mlx->file.textures[mlx->ray.texID];
    if (T->empty || !T->img || !T->img->pixels) {
        int y = mlx->ray.drawStart;
        while (y <= mlx->ray.drawEnd) {
            put_pixel(x, y, 0xAAAAAA, mlx->img);
            y++;
        }
        return;
    }

    mlx_texture_t *tex = T->img;
    int texW = tex->width;
    int texH = tex->height;
    uint32_t *pixels = (uint32_t *)tex->pixels;

    double wallX = (mlx->ray.side == 0)
        ? (mlx->ray.posY + mlx->ray.perpDist * mlx->ray.rayDirY)
        : (mlx->ray.posX + mlx->ray.perpDist * mlx->ray.rayDirX);
    wallX -= floor(wallX);

    int y = mlx->ray.drawStart;
    while (y <= mlx->ray.drawEnd) {
        double yPos = ((double)y - mlx->ray.drawStart)
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
