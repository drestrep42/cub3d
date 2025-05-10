/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:27:36 by igvisera          #+#    #+#             */
/*   Updated: 2025/05/10 20:11:40 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	move_strafe(double *newpos_x, double *newpos_y, \
						mlx_key_data_t key_data, t_mlx *mlx)
{
	double	strafe_dir;

	if (key_data.key == MLX_KEY_A)
		strafe_dir = -1.0;
	else
		strafe_dir = 1.0;
	*newpos_x += -mlx->sin_angle * mlx->speed * strafe_dir;
	*newpos_y += mlx->cos_angle * mlx->speed * strafe_dir;
}

static void	move_player_arrows(mlx_key_data_t key_data, t_mlx *mlx)
{
	double	dir;
	double	newpos_x;
	double	newpos_y;

	if (key_data.key == MLX_KEY_S)
		dir = -1.0;
	else
		dir = 1.0;
	newpos_x = mlx->player.pos_x;
	newpos_y = mlx->player.pos_y;
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_S)
	{
		newpos_x += mlx->cos_angle * mlx->speed * dir;
		newpos_y += mlx->sin_angle * mlx->speed * dir;
	}
	else if (key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_D)
		move_strafe(&newpos_x, &newpos_y, key_data, mlx);
	if (!touch(newpos_x, mlx->player.pos_y, &mlx->file.map))
		mlx->player.pos_x = newpos_x;
	if (!touch(mlx->player.pos_x, newpos_y, &mlx->file.map))
		mlx->player.pos_y = newpos_y;
}

void	move_player(mlx_key_data_t key_data, t_mlx *mlx)
{
	double	angle_speed;

	angle_speed = 0.08;
	mlx->speed = 3;
	if (key_data.key == MLX_KEY_LEFT)
		mlx->player.angle -= angle_speed;
	if (key_data.key == MLX_KEY_RIGHT)
		mlx->player.angle += angle_speed;
	if (mlx->player.angle >= 2 * PI)
		mlx->player.angle -= 2 * PI;
	if (mlx->player.angle < 0)
		mlx->player.angle += 2 * PI;
	mlx->cos_angle = cos(mlx->player.angle);
	mlx->sin_angle = sin(mlx->player.angle);
	if (key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_A || \
		key_data.key == MLX_KEY_S || key_data.key == MLX_KEY_D)
		move_player_arrows(key_data, mlx);
}

static int	set_player_position(t_player *player, t_map *map, int x, int y)
{
	char	c;

	c = map->coord[y][x].nbr;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		player->pos_x = (x + 0.5) * BLOCK;
		player->pos_y = (y + 0.5) * BLOCK;
		if (c == 'N')
			player->angle = 3 * PI / 2;
		else if (c == 'S')
			player->angle = PI / 2;
		else if (c == 'E')
			player->angle = 0;
		else if (c == 'W')
			player->angle = PI;
		player->angle += 0.02;
		map->coord[y][x].nbr = '0';
		return (1);
	}
	return (0);
}

void	init_player(t_player *player, t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->y_nbrs)
	{
		x = -1;
		while (++x < map->x_nbrs)
		{
			if (map->coord[y] != NULL && x < ft_strlen(map->raw_lines[y]))
			{
				if (set_player_position(player, map, x, y))
					return ;
			}
		}
	}
}
