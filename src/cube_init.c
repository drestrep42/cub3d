/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/25 16:02:57 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char worldMap[mapHeight][mapWidth] = {
    {'1','1','1','1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','0','0','1','0','0','1'},
    {'1','0','0','0','0','1','0','0',' ','1','S','0','1'},
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
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, img);  
    for (int i = 0; i < size; i++)
        put_pixel(x, y+i, color, img);
    for (int i = 0; i < size; i++)
        put_pixel(x+size, y+i, color, img);
    for (int i = 0; i < size; i++)
        put_pixel(x+i, y+size, color, img);
    
}

bool touch(double px, double py)
// bool touch(double px, double py, t_map *map)
{
    int x = (int)(px / BLOCK);
    int y = (int)(py / BLOCK);
    
    if (x < 0 || y < 0 || x >= mapWidth || y >= mapHeight)
        return true;
    if (worldMap[y][x] == '1')
    // if (map->coord[y][x].nbr == '1')
        return true;
    return false;
}

void move_player(mlx_key_data_t key_data, t_mlx *mlx)
// void move_player(mlx_key_data_t key_data, t_player *player)
{
    int speed = 3;
    double angle_speed = 0.2;
    double cos_angle = cos(mlx->player.angle);
    double sin_angle = sin(mlx->player.angle);

    //movimiento de la cam
    if (key_data.key == MLX_KEY_Q)
        mlx->player.angle -= angle_speed;
    if (key_data.key == MLX_KEY_E)
        mlx->player.angle += angle_speed;
    if (mlx->player.angle > 2 * PI)
        mlx->player.angle = 0;
    if (mlx->player.angle < 0)
        mlx->player.angle = 2 * PI;

    // movimiento del personaje
    if (key_data.key == MLX_KEY_UP)
    {
        double newPosX = mlx->player.posX + cos_angle * speed;
        double newPosY = mlx->player.posY + sin_angle * speed;
        if (!touch(newPosX, mlx->player.posY))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY))
            mlx->player.posY = newPosY;
    }
    if (key_data.key == MLX_KEY_DOWN)
    {
        double newPosX = mlx->player.posX - cos_angle * speed;
        double newPosY = mlx->player.posY - sin_angle * speed;
        if (!touch(newPosX, mlx->player.posY))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY))
            mlx->player.posY = newPosY;
    }
    if (key_data.key == MLX_KEY_RIGHT)
    {
        double newPosX = mlx->player.posX - sin_angle * speed;
        double newPosY = mlx->player.posY + cos_angle * speed;
        if (!touch(newPosX, mlx->player.posY))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY))
            mlx->player.posY = newPosY;
    }
    if (key_data.key == MLX_KEY_LEFT)
    {
        double newPosX = mlx->player.posX + sin_angle * speed;
        double newPosY = mlx->player.posY - cos_angle * speed;
        if (!touch(newPosX, mlx->player.posY))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY))
            mlx->player.posY = newPosY;
    }
}

static void key_callback(mlx_key_data_t key_data, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    (void)mlx;
    if (key_data.key == MLX_KEY_ESCAPE)
        exit(1);
    if (key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN ||
        key_data.key == MLX_KEY_RIGHT || key_data.key == MLX_KEY_LEFT ||
        key_data.key == MLX_KEY_Q || key_data.key == MLX_KEY_E)
        move_player(key_data, mlx);
}
void init_player(t_player *player)
{
    int y;
    int x;

    printf("pintamos el mapa\n");
    for (y = 0; y < mapHeight; y++)
    {
        for (x = 0; x < mapWidth; x++)
        {
            char c = worldMap[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                printf("accedes ??? x='%d' y='%d'\n", x, y);
                // Posición centrada en el bloque: se le suma 0.5 y se 
                // puede multiplicar por BLOCK si se usa coordenadas en píxeles
                // player->posX = x + 0.5;
                // player->posY = y + 0.5;
                player->posX = (x + 0.5) * BLOCK;
                player->posY = (y + 0.5) * BLOCK;
                if (c == 'N')
                    player->angle = 3 * PI / 2; // 270º
                else if (c == 'S')
                    player->angle = PI / 2;     // 90º
                else if (c == 'E')
                    player->angle = 0;          // 0º
                else if (c == 'W')
                    player->angle = PI;         // 180º

                worldMap[y][x] = '0'; // Elimina el marcador del mapa
                return;
            }
        }
    }
}


void clear_image(t_mlx *mlx)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, mlx->img);
}

// void draw_map(t_mlx *mlx)
// {
//     // t_points **map = mlx->file.map.coord;
//     int color = 0XAAAAAA;
//     for (int y = 0; y < mlx->file.map.y_nbrs; y++) {
//         for (int x = 0; x < mlx->file.map.x_nbrs; x++) {
//     // for (int y = 0; y < mapWidth; y++) {
//     //     for (int x = 0; x < mapHeight; x++) {
//             if (worldMap[y][x] == 1)
//                 draw_square(x * 64, y * 64, 64, color, mlx->img);
//         }
//     }
// }



// double ray_x = mlx->player.posX;
// double ray_y = mlx->player.posY;
// double cos_angle = cos(mlx->player.angle);
// double sin_angle = sin(mlx->player.angle);

// while (!touch(ray_x, ray_y))
// {
//     put_pixel(ray_x, ray_y, 0xAAAAAA, mlx->img);
//     ray_x += cos_angle;        
//     ray_y += sin_angle;        
// }

double distance(double x, double y)
{
    return (sqrt(x*x+y*y));
}

double init_distance(double x, double y, double x1, double y1, t_mlx *mlx)
{
    double delta_x = x1 - x;
    double delta_y = y1 - y;
    double angle = atan2(delta_y, delta_x) - mlx->player.angle;
    double dist = distance(delta_x, delta_y )* cos(angle);
    return (dist);
    
}

// void draw_line(t_mlx *mlx, float start_x, int i)
// {
//     double ray_x = mlx->player.posX;
//     double ray_y = mlx->player.posY;
//     double cos_angle = cos(start_x);
//     double sin_angle = sin(start_x);
    
//     while (!touch(ray_x, ray_y))
//     {
//         // put_pixel(ray_x, ray_y, 0xAA1111, mlx->img);//proyeccion de la vista del jugador
//         ray_x += cos_angle;        
//         ray_y += sin_angle;        
//     }
//     double dist = init_distance(mlx->player.posX, mlx->player.posY, ray_x, ray_y, mlx);
//     double height = (BLOCK/dist)*(WIDTH/2);
//     int start_y = (HEIGHT-height)/2;
//     int end = start_y +height;
//     while (start_y < end)
//     {
//         put_pixel(i, start_y, 0xAAAAAA, mlx->img);
//         start_y++;
//     }
    
// }

// void draw_line(t_mlx *mlx, float ray_angle, int screenX, t_texture textures[4])
// {
//     double ray_x = mlx->player.posX;
//     double ray_y = mlx->player.posY;
//     double cos_angle = cos(ray_angle);
//     double sin_angle = sin(ray_angle);
//     int side = -1; // Indicará si se golpeó una pared vertical (0) u horizontal (1)

//     // --- Algoritmo DDA (o similar) para encontrar el punto de colisión ---
//     // Por simplicidad se usa el bucle mientras(!touch(...)).
//     while (!touch(ray_x, ray_y))
//     {
//         // Aquí también podrías determinar si la colisión ocurrió en x o en y
//         // para definir la variable 'side'.
//         ray_x += cos_angle;
//         ray_y += sin_angle;
//     }

//     // Distancia con corrección "fishbowl"
//     double perpWallDist = init_distance(mlx->player.posX, mlx->player.posY, ray_x, ray_y, mlx);
    
//     // Altura de la pared proyectada
//     int lineHeight = (int)((BLOCK / perpWallDist) * (HEIGHT / 2));
//     int drawStart = (HEIGHT - lineHeight) / 2;
//     int drawEnd = drawStart + lineHeight;

//     // Calcular wallX (la posición exacta en la pared donde impacta el rayo, valor entre 0 y BLOCK)
//     double wallX;
//     if (side == 0) // Pared vertical
//         wallX = fmod(mlx->player.posY + perpWallDist * sin_angle, BLOCK);
//     else // Pared horizontal
//         wallX = fmod(mlx->player.posX + perpWallDist * cos_angle, BLOCK);

//     // Normalizar wallX a [0,1]
//     wallX /= BLOCK;

//     // Seleccionar la textura según la dirección:
//     // Por ejemplo: 0 = NO, 1 = SO, 2 = WE, 3 = EA.
//     int textureIndex;
//     if (side == 0)
//     {
//         if (cos_angle > 0)
//             textureIndex = 3; // Este (EA)
//         else
//             textureIndex = 2; // Oeste (WE)
//     }
//     else
//     {
//         if (sin_angle > 0)
//             textureIndex = 1; // Sur (SO)
//         else
//             textureIndex = 0; // Norte (NO)
//     }

//     // Obtener la textura seleccionada
//     mlx_texture_t *tex = textures[textureIndex].img;
//     int texWidth = tex->width;
//     int texHeight = tex->height;

//     // Calcular la columna de la textura (texX) a muestrear:
//     int texX = (int)(wallX * texWidth);
//     // Opcional: invertir horizontalmente según la dirección del rayo
//     if ((side == 0 && cos_angle > 0) || (side == 1 && sin_angle < 0))
//         texX = texWidth - texX - 1;

//     // Ahora recorremos cada píxel vertical desde drawStart hasta drawEnd y lo mapeamos a texY
//     for (int y = drawStart; y < drawEnd; y++)
//     {
//         // Calcula la posición relativa en la pared (0 en drawStart, 1 en drawEnd)
//         int d = y - drawStart; 
//         // Calcula texY proporcionalmente a la altura de la textura
//         int texY = (d * texHeight) / lineHeight;

//         // Obtener el color del píxel (suponiendo que 'pixels' es un array de char con RGBA, 4 bytes por píxel)
//         int pixelIndex = (texY * texWidth + texX) * 4;
//         unsigned char *pixels = tex->pixels;
//         // Armar el color en formato ARGB o RGBA (ajusta el orden segun MLX)
//         int color = (pixels[pixelIndex] << 24) | (pixels[pixelIndex + 1] << 16)
//                   | (pixels[pixelIndex + 2] << 8) | (pixels[pixelIndex + 3]);
                  
//         put_pixel(screenX, y, color, mlx->img);
//     }
// }

void draw_line(t_mlx *mlx, float ray_angle, int screenX, t_texture textures[4])
{
    // Posición inicial del rayo (en píxeles)
    double rayX = mlx->player.posX;
    double rayY = mlx->player.posY;

    // Componentes de la dirección del rayo
    double cos_angle = cos(ray_angle);
    double sin_angle = sin(ray_angle);

    // Coordenadas del cuadrante actual en el mapa (índices enteros)
    int mapX = (int)(rayX / BLOCK);
    int mapY = (int)(rayY / BLOCK);

    // Distancias parciales del rayo al siguiente borde (en cada eje)
    double deltaDistX = (cos_angle == 0) ? 1e30 : fabs(BLOCK / cos_angle);
    double deltaDistY = (sin_angle == 0) ? 1e30 : fabs(BLOCK / sin_angle);

    // Variables para determinar en qué dirección se avanza en el mapa
    int stepX, stepY;
    double sideDistX, sideDistY;

    // Calcular el step y la primera distancia lateral (sideDist) en X
    if (cos_angle < 0)
    {
        stepX = -1;
        sideDistX = (rayX - (mapX * BLOCK)) * deltaDistX / BLOCK;
    }
    else
    {
        stepX = 1;
        sideDistX = (((mapX + 1) * BLOCK) - rayX) * deltaDistX / BLOCK;
    }
    // Calcular el step y la primera distancia lateral (sideDist) en Y
    if (sin_angle < 0)
    {
        stepY = -1;
        sideDistY = (rayY - (mapY * BLOCK)) * deltaDistY / BLOCK;
    }
    else
    {
        stepY = 1;
        sideDistY = (((mapY + 1) * BLOCK) - rayY) * deltaDistY / BLOCK;
    }

    int side = -1;  // 0 para pared vertical, 1 para pared horizontal
    // Bucle DDA: avanzar hasta encontrar una pared ('1')
    while (1)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX / BLOCK;
            mapX += stepX;
            side = 0;  // Se golpea una pared vertical
        }
        else
        {
            sideDistY += deltaDistY / BLOCK;
            mapY += stepY;
            side = 1;  // Se golpea una pared horizontal
        }
        // Verifica que el índice esté dentro del rango del mapa
        if (mapX < 0 || mapY < 0 || mapX >= mapWidth || mapY >= mapHeight)
            break;
        // Si se encontró la pared, sal del bucle
        if (worldMap[mapY][mapX] == '1')
            break;
    }

    // Calcular distancia perpendicular a la pared para corregir el efecto "fishbowl"
    double perpWallDist;
    if (side == 0)
        perpWallDist = fabs((mapX * BLOCK - mlx->player.posX + (1 - stepX) * BLOCK * 0.5) / cos_angle);
    else
        perpWallDist = fabs((mapY * BLOCK - mlx->player.posY + (1 - stepY) * BLOCK * 0.5) / sin_angle);

    // Calcular la altura de la línea (pared) a proyectar en pantalla
    int lineHeight = (int)((BLOCK / perpWallDist) * (HEIGHT / 2));
    int drawStart = (HEIGHT - lineHeight) / 2;
    int drawEnd = drawStart + lineHeight;

    // Calcular wallX: el punto exacto donde el rayo impacta la pared
    double wallX;
    if (side == 0)
        wallX = mlx->player.posY + perpWallDist * sin_angle;
    else
        wallX = mlx->player.posX + perpWallDist * cos_angle;
    // Se reduce a un valor en [0, BLOCK]
    wallX = wallX - floor(wallX / BLOCK) * BLOCK;
    // Se normaliza a [0,1]
    wallX /= BLOCK;

    // Seleccionar la textura en función de la dirección del rayo
    int textureIndex;
    if (side == 0)
    {
        if (cos_angle > 0)
            textureIndex = 3;  // Este
        else
            textureIndex = 2;  // Oeste
    }
    else
    {
        if (sin_angle > 0)
            textureIndex = 1;  // Sur
        else
            textureIndex = 0;  // Norte
    }

    // Obtener la textura seleccionada y verificar que esté inicializada

	(void)textures;
    //printf("textureIndex '%d'\n", textureIndex);
    //printf("path '%s'\n", textures[textureIndex].path);
    if (!mlx->file.textures[textureIndex].img)
    {
       printf("no existe la texutra\n");
    }
    mlx_texture_t *tex = mlx->file.textures[textureIndex].img;
    if (!tex)
    {
        fprintf(stderr, "Error: La textura %d no se cargó correctamente.\n", textureIndex);
        exit(1);
        return;
    }
    int texWidth = tex->width;
    int texHeight = tex->height;

    // Calcular la columna de la textura a muestrear
    int texX = (int)(wallX * texWidth);
    // Invertir horizontalmente la textura según la dirección del rayo
    if ((side == 0 && cos_angle > 0) || (side == 1 && sin_angle < 0))
        texX = texWidth - texX - 1;

    // Recorrer cada píxel vertical entre drawStart y drawEnd para proyectar la pared
    for (int y = drawStart; y < drawEnd; y++)
    {
        int d = y - drawStart;
        int texY = (d * texHeight) / lineHeight;
        int pixelIndex = (texY * texWidth + texX) * 4;  // 4 bytes por píxel (RGBA)
        unsigned char *pixels = tex->pixels;
        int color = (pixels[pixelIndex] << 24) | (pixels[pixelIndex + 1] << 16)
                    | (pixels[pixelIndex + 2] << 8) | (pixels[pixelIndex + 3]);
        put_pixel(screenX, y, color, mlx->img);
    }
}



void draw_loop(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    // draw_square(mlx->player.posX, mlx->player.posY, 5, 0XAAAAAA, mlx->img);
    // draw_map(mlx);
    // create_line
    clear_image(mlx);

    for (int y = 0; y < HEIGHT / 2; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            put_pixel(x, y, 0xFF0000, mlx->img);// 0xAAAAAA
            // put_pixel(x, y, 0xFF0000, mlx->img);0xAAAAAA
        }
    }
    for (int y = HEIGHT / 2; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            put_pixel(x, y, 0x00FF00, mlx->img);
        }
    }
    // Renderizar las paredes y otros elementos del juego
    float fraction = PI / 3 / WIDTH;
    float start_x = mlx->player.angle - PI / 6;
    int i = 0;
    while (i < WIDTH)
    {
        draw_line(mlx, start_x, i, mlx->file.textures);
        // draw_line(mlx, start_x, i);
        start_x += fraction;
        i++;
    }

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
    // draw_square(WIDTH, HEIGHT, 10, 0XAAAAAA, mlx->img);
    init_player(&mlx->player);
    mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
    mlx_loop_hook(mlx->mlx_ptr, draw_loop, mlx);
    mlx_loop(mlx->mlx_ptr);
}

// TENGO Q USAR ESTO PARA BORRAR LA MEMORIA DE LAS PAREDES GUARDADAS
// mlx_delete_xpm42(xpm);