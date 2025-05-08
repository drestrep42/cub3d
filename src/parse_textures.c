/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:48 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/08 16:32:58 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*get_word(char *line)
{
	char	*word;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n' \
	&& line[i] != ' ' && line[i] != '\t')
		i++;
	word = ft_substr(line, 0, i);
	return (word);
}

void	texture_init(t_texture *texture, int cardinal, char *path)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(path);
	texture[cardinal].path = path;
	texture[cardinal].xpm = xpm;
	texture[cardinal].img = &xpm->texture;
	texture[cardinal].width = xpm->texture.width;
	texture[cardinal].height = xpm->texture.height;
	texture[cardinal].empty = false;
}

void	parse_textures(t_allocated *tobfreed, t_texture *texture, \
						int cardinal)
{
	int		fd;
	char	*path;
	int		i;

	i = ft_strlen(tobfreed->var1);
	while (tobfreed->var2[i] == ' ' || tobfreed->var2[i] == '\t')
		i++;
	path = get_word(tobfreed->var2 + i);
	i += ft_strlen(path);
	while (tobfreed->var2[i] == ' ' || tobfreed->var2[i] == '\t')
		i++;
	if (tobfreed->var2[i] != '\n')
	{
		free(path);
		free_allocated_and_exit(tobfreed, false, true, INVALID_TEXTURES);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		free_allocated_and_exit(tobfreed, false, true, strerror(errno));
	}
	close(fd);
	texture_init(texture, cardinal, path);
}
