/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:45:34 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/09 18:46:36 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	flags_init(t_allocated *tobfreed, bool rgb_flag, \
					bool textures_flag, bool gnl_flag)
{
	tobfreed->flags.rgb_flag = rgb_flag;
	tobfreed->flags.textures_flag = textures_flag;
	tobfreed->flags.gnl_flag = gnl_flag;
}

void	free_gnl(int fd)
{
	char	*aux;
	char	*line;

	aux = get_next_line(fd);
	while (aux != NULL)
	{
		line = aux;
		free(line);
		aux = get_next_line(fd);
	}
	free(aux);
}

void	free_rgb(t_allocated *tobfreed)
{
	free(tobfreed->var3[0]);
	free(tobfreed->var3[1]);
	free(tobfreed->var3[2]);
	free(tobfreed->var3);
}

void	free_textures(t_mlx *mlx, int path_flag)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (mlx->file.textures[i].xpm)
		{
			if (path_flag == 1)
				free(mlx->file.textures[i].path);
			mlx_delete_texture(&mlx->file.textures[i].xpm->texture);
			mlx->file.textures[i].xpm = NULL;
		}
	}
}
