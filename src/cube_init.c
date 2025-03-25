/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/25 20:00:37 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// static void key_callback(mlx_key_data_t key_data, void *param)
// {
//     t_mlx *mlx = (t_mlx *)param;

//     if (key_data.key == MLX_KEY_ESCAPE)
//         exit(1);
// 	// mlx_destroy_image(window->mlx, window->img.img_ptr);
// 	// window->img.img_ptr = mlx_new_image(window->mlx, WIDTH_WIN, HEIGHT_WIN);
// 	// window->img.img_pixel_ptr = mlx_get_data_addr(window->img.img_ptr,
// 	// 		&window->img.bits_per_pixel, &window->img.line_length,
// 	// 		&window->img.endian);
// 	printf("path: '%s'\n", mlx->file.textures[NO].path);
// }

void	cube_init(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	// mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
	// mlx_loop(mlx->mlx_ptr);
}
