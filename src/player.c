/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:27:36 by igvisera          #+#    #+#             */
/*   Updated: 2025/04/30 10:49:06 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void move_strafe(double *newPosX, double *newPosY, double sin_angle, double cos_angle, int speed, mlx_key_data_t key_data)
{
    double strafe_dir;

    if (key_data.key == MLX_KEY_LEFT)
        strafe_dir = -1.0;
    else
        strafe_dir = 1.0;
    *newPosX += -sin_angle * speed * strafe_dir;
    *newPosY +=  cos_angle * speed * strafe_dir;
}

static void move_player_arrows(mlx_key_data_t key_data, t_mlx *mlx, double cos_angle, double sin_angle, int speed)
{
    double dir;
    double newPosX;
    double newPosY;

    if (key_data.key == MLX_KEY_DOWN)
        dir = -1.0;
    else
        dir = 1.0;
    newPosX = mlx->player.posX;
    newPosY = mlx->player.posY;
    if (key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN)
    {
        newPosX += cos_angle * speed * dir;
        newPosY += sin_angle * speed * dir;
    }
    else if (key_data.key == MLX_KEY_RIGHT || key_data.key == MLX_KEY_LEFT)
        move_strafe(&newPosX, &newPosY, sin_angle, cos_angle, speed, key_data);
    if (!touch(newPosX, mlx->player.posY, &mlx->file.map, PLAYER_RADIUS))
        mlx->player.posX = newPosX;
    if (!touch(mlx->player.posX, newPosY, &mlx->file.map, PLAYER_RADIUS))
        mlx->player.posY = newPosY;
}

void move_player(mlx_key_data_t key_data, t_mlx *mlx)
{
    int speed;
    double angle_speed;
    double cos_angle;
    double sin_angle;

    speed = 3;
    angle_speed = 0.2;
    if (key_data.key == MLX_KEY_Q)
        mlx->player.angle -= angle_speed;
    if (key_data.key == MLX_KEY_E)
        mlx->player.angle += angle_speed;
    if (mlx->player.angle >= 2 * PI)
        mlx->player.angle -= 2 * PI;
    if (mlx->player.angle < 0)
        mlx->player.angle += 2 * PI;

    cos_angle = cos(mlx->player.angle);
    sin_angle = sin(mlx->player.angle);
    if (key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN ||
        key_data.key == MLX_KEY_RIGHT || key_data.key == MLX_KEY_LEFT)
        move_player_arrows(key_data, mlx, cos_angle, sin_angle, speed);
}


static int set_player_position(t_player *player, t_map *map, int x, int y)
{
    char c;

    c = map->coord[y][x].nbr;
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
        return (1);
    }
    return (0);
}


void init_player(t_player *player, t_map *map)
{
    int y;
    int x;

    y = -1;
    while (++y < map->y_nbrs)
    {
        x = -1;
        while (++x < map->x_nbrs)
        {
            if (map->coord[y] != NULL && x < ft_strlen(map->raw_lines[y]))
            {
                if (set_player_position(player, map, x, y))
                    return;    
            }
        }
    }
}
