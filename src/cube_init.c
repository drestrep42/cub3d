/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/24 18:13:09 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char worldMap[mapHeight][mapWidth] = {
    {'1','1','1','1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','0','0','1','0','0','1'},
    {'1','0','0','0','0','1','0','0','0','1','S','0','1'},
    {'1','0','1','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','1','1','1','1','1','0','1'},
    {'1','0','0','0','0','0','1','1','1','1','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1','1','1','1'}
};


void put_pixel(int x, int y, int color, mlx_image_t *img)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;
    mlx_put_pixel(img, x, y, color);
}

void draw_square(int x, int y, int size, int color, mlx_image_t *img)
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

// void draw_map(t_mlx *mlx)
// {
//     int color = 0xAAAAAA;

//     for (int y = 0; y < mlx->file.map.y_nbrs; y++)
//     {
//         // Calculamos la longitud real de esta fila
//         size_t row_len = ft_strlen(mlx->file.map.raw_lines[y]);

//         for (int x = 0; x < mlx->file.map.x_nbrs; x++)
//         {
//             // Si x supera la longitud de la línea, saltamos
//             if ((size_t)x >= row_len)
//                 continue;

//             if (mlx->file.map.coord[y][x].nbr == '1')
//                 draw_square(x * BLOCK, y * BLOCK,
//                             BLOCK, color, mlx->img);
//         }
//     }
// }

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

void draw_line(t_mlx *mlx, float start_x, int i)
{
    double ray_x = mlx->player.posX;
    double ray_y = mlx->player.posY;
    double cos_angle = cos(start_x);
    double sin_angle = sin(start_x);
    int steps = 0;
    const int MAX_STEPS = 1000;

    while (!touch(ray_x, ray_y, &mlx->file.map) && steps < MAX_STEPS)
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
        steps++;
    }

    double dist = init_distance(mlx->player.posX, mlx->player.posY, ray_x, ray_y, mlx);
    double proj_dist = (WIDTH / 2) / tan(PI / 6);
    double height = (BLOCK / dist) * proj_dist;

    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;

    if (start_y < 0) start_y = 0;
    if (end > HEIGHT) end = HEIGHT;

    while (start_y < end)
    {
        put_pixel(i, start_y, 0xAAAAAA, mlx->img);
        start_y++;
    }
}

// void draw_loop(void *param)
// {
//     t_mlx *mlx = (t_mlx *)param;
//     clear_image(mlx);
//     draw_map(mlx);

//     int y = 0;
//     while (y < HEIGHT / 2)
//     {
//         int x = 0;
//         while (x < WIDTH)
//         {
//             put_pixel(x, y, 0xFF0000, mlx->img);
//             x++;
//         }
//         y++;
//     }

//     y = HEIGHT / 2;
//     while (y < HEIGHT)
//     {
//         int x = 0;
//         while (x < WIDTH)
//         {
//             put_pixel(x, y, 0x00FF00, mlx->img);
//             x++;
//         }
//         y++;
//     }

//     float fraction = PI / 3 / WIDTH;
//     float start_x = mlx->player.angle - PI / 6;
//     int i = 0;
//     while (i < WIDTH)
//     {
//         draw_line(mlx, start_x, i);
//         start_x += fraction;
//         i++;
//     }

//     mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
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
    double wallX = (side == 0)
        ? (posY + perpDist * rayDirY)
        : (posX + perpDist * rayDirX);
    wallX -= floor(wallX);

    // 13b) texX
    int texX = (int)(wallX * texW);
    if ((side == 0 && rayDirX > 0) ||
        (side == 1 && rayDirY < 0))
        texX = texW - texX - 1;

    // 13c) paso vertical en la textura
    double stepTex = (double)texH / lineHeight;
    double texPos  = (drawStart - HEIGHT/2 + lineHeight/2) * stepTex;

    // 13d) bucle de pintado
    for (int y = drawStart; y <= drawEnd; y++) {
        int texY = ((int)texPos) & (texH - 1);
        texPos += stepTex;
        uint32_t color = pixels[ texY * texW + texX ];
        put_pixel(screenX, y, color, mlx->img);
    }
}

int	get_color(t_mlx *mlx, int mode)
{

    if (mode == 1)
        return ((mlx->file.ceiling.color[R] << 24) | 
            ((mlx->file.ceiling.color[G] & 0xFF) << 16) | 
            ((mlx->file.ceiling.color[B] & 0xFF) << 8) | 
            ((255 & 0xFF)));
    else
        return ((mlx->file.floor.color[R] << 24) | 
            ((mlx->file.floor.color[G] & 0xFF) << 16) | 
            ((mlx->file.floor.color[B] & 0xFF) << 8) | 
            ((255 & 0xFF)));
}

void draw_loop(void *param)
{
    t_mlx *mlx = (t_mlx *)param;

    clear_image(mlx);

    // cielo / suelo
    for (int y = 0; y < HEIGHT/2; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, get_color(mlx, 1), mlx->img);
    for (int y = HEIGHT/2; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, get_color(mlx, 0), mlx->img);

    // trazo rayos
    double startAngle = mlx->player.angle - (PI/3)/2;
    double angleStep  = (PI/3) / WIDTH;
    for (int i = 0; i < WIDTH; i++, startAngle += angleStep)
        cast_single_ray(mlx, startAngle, i);

    mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
}


// t_color	get_color(int col)
// {
// 	t_color	c;

// 	c.t = (col >> 24) & 0xFF;
// 	c.r = (col >> 16) & 0xFF;
// 	c.g = (col >> 8) & 0xFF;
// 	c.b = col & 0xFF;
// 	return (c);
// }



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


//----------------------------------------------------

// void draw_line(t_mlx *mlx, double ray_angle, int screenX)
// {
//     // Posición inicial del rayo
//     double rayX = mlx->player.posX;
//     double rayY = mlx->player.posY;

//     // Dirección del rayo
//     double cos_a = cos(ray_angle);
//     double sin_a = sin(ray_angle);

//     // Coordenadas de celda actual en el mapa
//     int mapX = (int)(rayX / BLOCK);
//     int mapY = (int)(rayY / BLOCK);

//     // Distancia entre intersecciones de líneas de la rejilla
//     double deltaDistX = (cos_a == 0) ? 1e30 : fabs(BLOCK / cos_a);
//     double deltaDistY = (sin_a == 0) ? 1e30 : fabs(BLOCK / sin_a);

//     int stepX, stepY;
//     double sideDistX, sideDistY;
//     int side; // 0: vertical, 1: horizontal

//     // Cálculo de sideDist iniciales
//     if (cos_a < 0) {
//         stepX = -1;
//         sideDistX = (rayX - mapX * BLOCK) * deltaDistX;
//     } else {
//         stepX =  1;
//         sideDistX = ((mapX + 1) * BLOCK - rayX) * deltaDistX;
//     }
//     if (sin_a < 0) {
//         stepY = -1;
//         sideDistY = (rayY - mapY * BLOCK) * deltaDistY;
//     } else {
//         stepY =  1;
//         sideDistY = ((mapY + 1) * BLOCK - rayY) * deltaDistY;
//     }

//     // Bucle DDA: avanzar celda a celda
//     while (1) {
//         if (sideDistX < sideDistY) {
//             sideDistX += deltaDistX;
//             mapX += stepX;
//             side = 0;
//         } else {
//             sideDistY += deltaDistY;
//             mapY += stepY;
//             side = 1;
//         }
//         // Fuera de mapa
//         if (mapX < 0 || mapY < 0 || mapX >= mlx->file.map.x_nbrs || mapY >= mlx->file.map.y_nbrs)
//             return;
//         // Impacto con pared
//         if (mlx->file.map.coord[mapY][mapX].nbr == '1')
//             break;
//     }

//     // Distancia perpendicular
//     double perpDist;
//     if (side == 0)
//         perpDist = (mapX - mlx->player.posX / BLOCK + (1 - stepX) / 2.0) * BLOCK / cos_a;
//     else
//         perpDist = (mapY - mlx->player.posY / BLOCK + (1 - stepY) / 2.0) * BLOCK / sin_a;

//     // Altura de línea
//     double projDist = (WIDTH / 2.0) / tan(PI / 6.0);
//     int lineHeight = (int)((BLOCK / perpDist) * projDist);
//     int drawStart = (HEIGHT - lineHeight) / 2;
//     int drawEnd   = drawStart + lineHeight;
//     if (drawStart < 0) drawStart = 0;
//     if (drawEnd   > HEIGHT) drawEnd   = HEIGHT;

//     // Cálculo de wallX para texturizado
//     double wallX;
//     if (side == 0)
//         wallX = rayY + perpDist * sin_a;
//     else
//         wallX = rayX + perpDist * cos_a;
//     wallX = fmod(wallX, BLOCK) / BLOCK;

//     // Selección de textura (0=Norte,1=Sur,2=Oeste,3=Este)
//     int texIndex;
//     if      (side == 0 && cos_a > 0)  texIndex = 2;
//     else if (side == 0 && cos_a < 0)  texIndex = 3;
//     else if (side == 1 && sin_a > 0)  texIndex = 1;
//     else                               texIndex = 0;

//     // Fallback color sólido
//     mlx_texture_t *tex = mlx->file.textures[texIndex].img;
//     if (!tex || !tex->pixels) {
//         int wallColor = (side == 0 ? 0xAAAAAA : 0x888888);
//         for (int y = drawStart; y < drawEnd; y++)
//             put_pixel(screenX, y, wallColor, mlx->img);
//         return;
//     }

//     // Muestreo de textura
//     int texW = tex->width;
//     int texH = tex->height;
//     int texX = (int)(wallX * texW);
//     if (texX < 0) texX = 0;
//     if (texX >= texW) texX = texW - 1;

//     double stepTex = (double)texH / lineHeight;
//     double texPos = (drawStart - (HEIGHT - lineHeight) / 2) * stepTex;
//     unsigned char *pix = tex->pixels;
//     for (int y = drawStart; y < drawEnd; y++) {
//         int texY = (int)texPos;
//         if (texY < 0) texY = 0;
//         if (texY >= texH) texY = texH - 1;
//         texPos += stepTex;

//         int idx = (texY * texW + texX) * 4;
//         int color = (pix[idx] << 24) |
//                     (pix[idx + 1] << 16) |
//                     (pix[idx + 2] << 8) |
//                      pix[idx + 3];
//         put_pixel(screenX, y, color, mlx->img);
//     }
// }



