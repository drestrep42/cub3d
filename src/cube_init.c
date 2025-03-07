/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/07 12:35:26 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cube_init(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
}
