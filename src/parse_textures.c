/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:48 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/30 17:50:14 by drestrep         ###   ########.fr       */
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

void	parse_textures(t_texture *texture, int cardinal, \
						char **line, char *word)
{
	xpm_t	*xpm;
	int		fd;
	char	*path;

	*line += ft_strlen(word);
	while (**line == ' ' || **line == '\t')
		(*line)++;
	path = get_word(*line);
	*line += ft_strlen(path);
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (**line != '\n')
		ft_exit(INVALID_TEXTURES);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit(strerror(errno));
	close(fd);
	xpm = mlx_load_xpm42(path);
	texture[cardinal].path = path;
	texture[cardinal].xpm = xpm;
	texture[cardinal].img = &xpm->texture;
	texture[cardinal].width = xpm->texture.width;
	texture[cardinal].height = xpm->texture.height;
	texture[cardinal].empty = false;
}
