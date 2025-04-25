/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/25 20:48:50 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void put_pixel(int x, int y, uint32_t color, mlx_image_t *img)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;

	uint32_t color_swapped = 0;
	for (int i = 0; i < 4; i++)
	{
		color_swapped <<= 8;
		color_swapped |= (0xff & color);
		color >>= 8;
	}
    mlx_put_pixel(img, x, y, color_swapped | 0xff);
}

void draw_square(int x, int y, int size, uint32_t color, mlx_image_t *img)
{
    int i = 0;
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
    int x = (int)(px / BLOCK);
    int y = (int)(py / BLOCK);

    if (x < 0 || y < 0 || x >= map->x_nbrs || y >= map->y_nbrs)
        return true;
    if (map->coord[y][x].nbr == '1')
        return true;
    return false;
}

void move_player(mlx_key_data_t key_data, t_mlx *mlx)
{
    const int speed = 3;
    const double angle_speed = 0.2;

    if (key_data.key == MLX_KEY_Q)
        mlx->player.angle -= angle_speed;
    if (key_data.key == MLX_KEY_E)
        mlx->player.angle += angle_speed;

    if (mlx->player.angle >= 2 * PI)
        mlx->player.angle -= 2 * PI;
    if (mlx->player.angle < 0)
        mlx->player.angle += 2 * PI;

    double cos_angle = cos(mlx->player.angle);
    double sin_angle = sin(mlx->player.angle);

    if (key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN ||
        key_data.key == MLX_KEY_RIGHT || key_data.key == MLX_KEY_LEFT)
    {
        double dir = (key_data.key == MLX_KEY_DOWN) ? -1.0 : 1.0;
        double newPosX = mlx->player.posX;
        double newPosY = mlx->player.posY;
        if (key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN)
        {
            newPosX += cos_angle * speed * dir;
            newPosY += sin_angle * speed * dir;
        }
        else if (key_data.key == MLX_KEY_RIGHT || key_data.key == MLX_KEY_LEFT)
        {
            double strafe_dir = (key_data.key == MLX_KEY_LEFT) ? -1.0 : 1.0;
            newPosX += -sin_angle * speed * strafe_dir;
            newPosY +=  cos_angle * speed * strafe_dir;
        }
        if (!touch(newPosX, mlx->player.posY, &mlx->file.map))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY, &mlx->file.map))
            mlx->player.posY = newPosY;
    }
}

static void key_callback(mlx_key_data_t key_data, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    if (key_data.key == MLX_KEY_ESCAPE)
        exit(1);
    if (key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN ||
        key_data.key == MLX_KEY_RIGHT || key_data.key == MLX_KEY_LEFT ||
        key_data.key == MLX_KEY_Q || key_data.key == MLX_KEY_E)
        move_player(key_data, mlx);
}

void init_player(t_player *player, t_map *map)
{
    int y = 0;
    printf("Inicializando el jugador...\n");
    while (y < map->y_nbrs)
    {
        int x = 0;
        while (x < map->x_nbrs)
        {
            printf("y='%d', x='%d'\n", y, x);
            if (map->coord[y] != NULL && x < ft_strlen(map->raw_lines[y]))
            {
                char c = map->coord[y][x].nbr;
                if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                {
                    player->posX = (x + 0.5) * BLOCK;
                    player->posY = (y + 0.5) * BLOCK;
                    if (c == 'N')
                        player->angle = 3 * PI / 2;
                    else if (c == 'S')
                        player->angle = PI / 2;
                    else if (c == 'E')
                        player->angle = 0;
                    else if (c == 'W')
                        player->angle = PI;
                    map->coord[y][x].nbr = '0';
                    return;
                }
            }
            x++;
        }
        y++;
    }
}

void clear_image(t_mlx *mlx)
{
    int y = 0;
    while (y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
        {
            put_pixel(x, y, 0, mlx->img);
            x++;
        }
        y++;
    }
}

double distance(double x, double y)
{
    return sqrt(x * x + y * y);
}

double init_distance(double x, double y, double x1, double y1, t_mlx *mlx)
{
    double delta_x = x1 - x;
    double delta_y = y1 - y;
    double angle = atan2(delta_y, delta_x) - mlx->player.angle;
    return distance(delta_x, delta_y) * cos(angle);
}

// void draw_line(t_mlx *mlx, float start_x, int i)
// {
//     double ray_x = mlx->player.posX;
//     double ray_y = mlx->player.posY;
//     double cos_angle = cos(start_x);
//     double sin_angle = sin(start_x);
//     int steps = 0;
//     const int MAX_STEPS = 1000;

//     while (!touch(ray_x, ray_y, &mlx->file.map) && steps < MAX_STEPS)
//     {
//         ray_x += cos_angle;
//         ray_y += sin_angle;
//         steps++;
//     }

//     double dist = init_distance(mlx->player.posX, mlx->player.posY, ray_x, ray_y, mlx);
//     double proj_dist = (WIDTH / 2) / tan(PI / 6);
//     double height = (BLOCK / dist) * proj_dist;

//     int start_y = (HEIGHT - height) / 2;
//     int end = start_y + height;

//     if (start_y < 0) start_y = 0;
//     if (end > HEIGHT) end = HEIGHT;

//     while (start_y < end)
//     {
//         put_pixel(i, start_y, 0xAAAAAA, mlx->img);
//         start_y++;
//     }
// }

// nueva versión de draw_line => cast_single_ray
//-----------------------

// void cast_single_ray(t_mlx *mlx, double rayAngle, int screenX)
// {
//     const double FOV           = PI / 3.0;
//     const double projPlaneDist = (screenWidth / 2.0) / tan(FOV / 2.0);

//     // Paso 1: jugador en celdas
//     double posX = mlx->player.posX / BLOCK;
//     double posY = mlx->player.posY / BLOCK;

//     // Paso 2: dirección del rayo
//     double rayDirX = cos(rayAngle);
//     double rayDirY = sin(rayAngle);

//     // Paso 3: celda inicial
//     int mapX = (int)posX;
//     int mapY = (int)posY;

//     // Paso 4: distancias delta
//     double deltaDistX = fabs(1.0 / rayDirX);
//     double deltaDistY = fabs(1.0 / rayDirY);

//     // Paso 5: calcular step y sideDist
//     int stepX, stepY;
//     double sideDistX, sideDistY;
//     if (rayDirX < 0)
//     {
//         stepX     = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//     }
//     else
//     {
//         stepX     = +1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//     }
//     if (rayDirY < 0)
//     {
//         stepY     = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//     }
//     else
//     {
//         stepY     = +1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//     }

//     // Paso 6: DDA hasta el muro
//     int hit = 0, side;
//     while (!hit)
//     {
//         if (sideDistX < sideDistY)
//         {
//             sideDistX += deltaDistX;
//             mapX      += stepX;
//             side       = 0;
//         }
//         else
//         {
//             sideDistY += deltaDistY;
//             mapY      += stepY;
//             side       = 1;
//         }
//         // fuera de mapa?
//         if (mapX < 0 || mapY < 0
//          || mapX >= mlx->file.map.x_nbrs
//          || mapY >= mlx->file.map.y_nbrs)
//         {
//             hit = 1;
//             break;
//         }
//         if (mlx->file.map.coord[mapY][mapX].nbr == '1')
//             hit = 1;
//     }

//     // Paso 7: distancia perpendicular en celdas
//     double perpDist;
//     if (side == 0)
//         perpDist = ((mapX - posX) + (1 - stepX) * 0.5) / rayDirX;
//     else
//         perpDist = ((mapY - posY) + (1 - stepY) * 0.5) / rayDirY;

//     // Paso 8: altura de línea en píxeles
//     int lineHeight = (int)(projPlaneDist / perpDist);

//     // Paso 9: start/end en Y
//     int drawStart = -lineHeight/2 + screenHeight/2;
//     if (drawStart < 0) drawStart = 0;
//     int drawEnd   = lineHeight/2 + screenHeight/2;
//     if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

//     // Paso 10: elegir textura de muro
//     int texID;
//     if (side == 0)
//         texID = (rayDirX > 0) ? SO : NO;
//     else
//         texID = (rayDirY > 0) ? WE : EA;
//     t_texture *T = &mlx->file.textures[texID];

//     // Paso 11: calcular coordenada X en textura
//     double wallX = (side == 0)
//                  ? posY + perpDist * rayDirY
//                  : posX + perpDist * rayDirX;
//     wallX -= floor(wallX);

//     int texX = (int)(wallX * (double)T->img->width);
//     if ((side == 0 && rayDirX > 0) ||
//         (side == 1 && rayDirY < 0))
//         texX = T->img->width - texX - 1;

//     // Paso 12: paso vertical y posición inicial
//     double stepTex = 1.0 * T->img->height / lineHeight;
//     double texPos  = (drawStart - screenHeight/2 + lineHeight/2) * stepTex;

//     // Paso 13: pintar columna
//     for (int y = drawStart; y <= drawEnd; y++)
//     {
//         int texY = (int)texPos & (T->img->height - 1);
//         texPos += stepTex;
//         uint32_t color = ((uint32_t*)T->img->pixels)[texY * T->img->width + texX];
//         put_pixel(screenX, y, color, mlx->img);
//     }
// }
//------------------
void cast_single_ray(t_mlx *mlx, double rayAngle, int screenX)
{
    // 1) Parámetros de cámara
    const double FOV           = PI / 3.0;
    const double projPlaneDist = (WIDTH / 2.0) / tan(FOV / 2.0);

    // 2) Posición del jugador en unidades de celda
    double posX = mlx->player.posX / BLOCK;
    double posY = mlx->player.posY / BLOCK;

    // 3) Dirección del rayo
    double rayDirX = cos(rayAngle);
    double rayDirY = sin(rayAngle);

    // 4) Celda inicial
    int mapX = (int)posX;
    int mapY = (int)posY;

    // 5) Distancias delta
    double deltaDistX = fabs(1.0 / rayDirX);
    double deltaDistY = fabs(1.0 / rayDirY);

    // 6) Cálculo de step y sideDist
    int stepX, stepY;
    double sideDistX, sideDistY;
    if (rayDirX < 0) {
        stepX     = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX     = +1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0) {
        stepY     = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY     = +1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    // 7) DDA: avanzamos hasta chocar con '1'
    int hit = 0, side;
    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX      += stepX;
            side       = 0;
        } else {
            sideDistY += deltaDistY;
            mapY      += stepY;
            side       = 1;
        }
        // fuera de mapa?
        if (mapX < 0 || mapY < 0 ||
            mapX >= mlx->file.map.x_nbrs ||
            mapY >= mlx->file.map.y_nbrs)
        {
            hit = 1;
            break;
        }
        if (mlx->file.map.coord[mapY][mapX].nbr == '1')
            hit = 1;
    }

    // 8) Distancia perpendicular (en celdas)
    double perpDist = (side == 0)
        ? ((mapX - posX) + (1 - stepX) * 0.5) / rayDirX
        : ((mapY - posY) + (1 - stepY) * 0.5) / rayDirY;

    // 9) Altura de la línea (en píxeles)
    int lineHeight = (int)(projPlaneDist / perpDist);

    // 10) Límite superior/inferior de la línea
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

    // 11) Seleccionamos la textura correcta
    int texID;
    if (side == 0)
        texID = (rayDirX > 0) ? SO : NO;
    else
        texID = (rayDirY > 0) ? WE : EA;
    t_texture *T = &mlx->file.textures[texID];

    // 12) Si no hay textura (o puntero nulo), dibujamos gris
    if (T->empty || T->img == NULL || T->img->pixels == NULL) {
        for (int y = drawStart; y <= drawEnd; y++)
            put_pixel(screenX, y, 0xAAAAAA, mlx->img);
        return;
    }

    // 13) Muestreamos la textura
    mlx_texture_t *tex   = T->img;
    int            texW  = tex->width;
    int            texH  = tex->height;
    uint32_t      *pixels = (uint32_t *)tex->pixels;

    // 13a) Cálculo de wallX (0.0–1.0)
    double x_pos = (side == 0)
        ? (posY + perpDist * rayDirY)
        : (posX + perpDist * rayDirX);
    x_pos -= floor(x_pos);

    // 13d) bucle de pintado
    for (int y = drawStart; y <= drawEnd; y++) {
		double y_pos = ((double)y - drawStart) / ((double)drawEnd - drawStart);

        // int texY = ((int)texPos) + (texH - 1);
        uint32_t r = (int)(x_pos * 255);
        uint32_t g = (int)(y_pos * 255);

		if (y_pos < 0 || y_pos > 1)
			ft_exit("y_pos out range");
		if (x_pos < 0 || x_pos > 1)
			ft_exit("x_pos out range");
		uint32_t color = pixels[(int)floor(x_pos * (texW - 1)) + (int)floor(y_pos * (texH - 1)) * (texW)];
        put_pixel(screenX, y, color, mlx->img);
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

void draw_loop(void *param)
{
    t_mlx *mlx = (t_mlx *)param;

    clear_image(mlx);
    for (int y = 0; y < HEIGHT/2; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, get_color(mlx, 1), mlx->img);
    for (int y = HEIGHT/2; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, get_color(mlx, 0), mlx->img);
    double startAngle = mlx->player.angle - (PI/3)/2;
    double angleStep  = (PI/3) / WIDTH;
    for (int i = 0; i < WIDTH; i++, startAngle += angleStep)
        cast_single_ray(mlx, startAngle, i);
    mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
}

void cube_init(t_mlx *mlx)
{
    mlx->width = WIDTH;
    mlx->height = HEIGHT;
    mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
    if (!mlx->mlx_ptr)
        ft_exit("Error al inicializar MLX");

    mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
    if (!mlx->img)
        ft_exit("Error al crear la imagen");

    printf("map->y_nbrs: %d, map->x_nbrs: %d\n", mlx->file.map.y_nbrs, mlx->file.map.x_nbrs);
    init_player(&mlx->player, &mlx->file.map);

    mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
    mlx_loop_hook(mlx->mlx_ptr, draw_loop, mlx);
    mlx_loop(mlx->mlx_ptr);
}
