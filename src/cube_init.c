/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/10 19:14:15 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	key_callback(mlx_key_data_t key_data, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		free_all(mlx, 1);
		exit(1);
	}
	if (key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN || \
		key_data.key == MLX_KEY_RIGHT || key_data.key == MLX_KEY_LEFT || \
		key_data.key == MLX_KEY_Q || key_data.key == MLX_KEY_E)
		move_player(key_data, mlx);
}

void	draw_loop(void *param)
{
	t_mlx	*mlx;
	double	startangle;
	double	anglestep;
	int		i;

	mlx = (t_mlx *)param;
	clear_image(mlx);
	print_sky_and_floor(mlx);
	startangle = mlx->player.angle - (PI / 3) / 2;
	anglestep = (PI / 3) / WIDTH;
	i = -1;
	while (++i < WIDTH)
	{
		cast_single_ray(mlx, startangle, i);
		startangle += anglestep;
	}
	mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
}

void	cube_init(t_mlx *mlx)
{
	mlx->width = WIDTH;
	mlx->height = HEIGHT;
	mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!mlx->mlx_ptr)
		ft_exit("Init MLX");
	mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (!mlx->img)
		ft_exit("clear image");
	init_player(&mlx->player, &mlx->file.map);
	mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
	mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
	mlx_loop_hook(mlx->mlx_ptr, draw_loop, mlx);
	mlx_loop(mlx->mlx_ptr);
}
