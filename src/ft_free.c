/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:35:59 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/07 17:37:11 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_all(t_mlx mlx)
{
	free(mlx.file.textures[NO]);
	free(mlx.file.textures[SO]);
	free(mlx.file.textures[EA]);	
	free(mlx.file.textures[WE]);
}
