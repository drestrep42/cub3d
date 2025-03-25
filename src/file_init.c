/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:41:55 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/25 17:42:04 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	file_init(t_file *file)
{
	file->textures[NO].empty = true;
	file->textures[SO].empty = true;
	file->textures[EA].empty = true;
	file->textures[WE].empty = true;
	file->ceiling.empty = true;
	file->floor.empty = true;
}
