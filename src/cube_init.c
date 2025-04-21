/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/16 20:06:02 by drestrep         ###   ########.fr       */
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
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, img);  
    for (int i = 0; i < size; i++)
        put_pixel(x, y+i, color, img);
    for (int i = 0; i < size; i++)
        put_pixel(x+size, y+i, color, img);
    for (int i = 0; i < size; i++)
        put_pixel(x+i, y+size, color, img);
    
}

bool touch(double px, double py, t_map *map)
{
    int x = (int)(px / BLOCK);
    int y = (int)(py / BLOCK);
    
    if (x < 0 || y < 0 || x >= map->x_nbrs || y >= map->y_nbrs)
        return true;
    // Se asume que la pared se marca con el caracter '1'
    if (map->coord[y][x].nbr == '1')
        return true;
    return false;
}

void move_player(mlx_key_data_t key_data, t_mlx *mlx)
{
    int speed = 3;
    double angle_speed = 0.2;
    double cos_angle = cos(mlx->player.angle);
    double sin_angle = sin(mlx->player.angle);

    // Rotación de la cámara
    if (key_data.key == MLX_KEY_Q)
        mlx->player.angle -= angle_speed;
    if (key_data.key == MLX_KEY_E)
        mlx->player.angle += angle_speed;
    if (mlx->player.angle > 2 * PI)
        mlx->player.angle = 0;
    if (mlx->player.angle < 0)
        mlx->player.angle = 2 * PI;

    // Movimiento del personaje
    if (key_data.key == MLX_KEY_UP)
    {
        double newPosX = mlx->player.posX + cos_angle * speed;
        double newPosY = mlx->player.posY + sin_angle * speed;
        if (!touch(newPosX, mlx->player.posY, &mlx->file.map))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY, &mlx->file.map))
            mlx->player.posY = newPosY;
    }
    if (key_data.key == MLX_KEY_DOWN)
    {
        double newPosX = mlx->player.posX - cos_angle * speed;
        double newPosY = mlx->player.posY - sin_angle * speed;
        if (!touch(newPosX, mlx->player.posY, &mlx->file.map))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY, &mlx->file.map))
            mlx->player.posY = newPosY;
    }
    if (key_data.key == MLX_KEY_RIGHT)
    {
        double newPosX = mlx->player.posX - sin_angle * speed;
        double newPosY = mlx->player.posY + cos_angle * speed;
        if (!touch(newPosX, mlx->player.posY, &mlx->file.map))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY, &mlx->file.map))
            mlx->player.posY = newPosY;
    }
    if (key_data.key == MLX_KEY_LEFT)
    {
        double newPosX = mlx->player.posX + sin_angle * speed;
        double newPosY = mlx->player.posY - cos_angle * speed;
        if (!touch(newPosX, mlx->player.posY, &mlx->file.map))
            mlx->player.posX = newPosX;
        if (!touch(mlx->player.posX, newPosY, &mlx->file.map))
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

void init_player(t_player *player, t_map *map)
{
    int y, x;
    //printf("Inicializando el jugador...\n");
    for (y = 0; y < map->y_nbrs; y++)
    {
        for (x = 0; x < map->x_nbrs; x++)
        {
            //printf("y='%d', x='%d'\n", y, x);
            if (map->coord[y] != NULL && x < ft_strlen(map->raw_lines[y])) {
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
        }
    }
}



void clear_image(t_mlx *mlx)
{
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, mlx->img);
}

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

void draw_line(t_mlx *mlx, float start_x, int i)
{
    double ray_x = mlx->player.posX;
    double ray_y = mlx->player.posY;
    double cos_angle = cos(start_x);
    double sin_angle = sin(start_x);
    
    while (!touch(ray_x, ray_y, &mlx->file.map))
    {
        ray_x += cos_angle;        
        ray_y += sin_angle;        
    }
    double dist = init_distance(mlx->player.posX, mlx->player.posY, ray_x, ray_y, mlx);
    double height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;
    while (start_y < end)
    {
        put_pixel(i, start_y, 0xAAAAAA, mlx->img);
        start_y++;
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
        draw_line(mlx, start_x, i);
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
    printf("map->y_nbrs: %d, map->x_nbrs: %d\n", mlx->file.map.y_nbrs, mlx->file.map.x_nbrs);
    init_player(&mlx->player, &mlx->file.map);
    mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
    mlx_loop_hook(mlx->mlx_ptr, draw_loop, mlx);
    mlx_loop(mlx->mlx_ptr);
}
 