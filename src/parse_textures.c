/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:48 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/16 20:05:10 by drestrep         ###   ########.fr       */
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
	char	*path;
	int		fd;

	*line += ft_strlen(word);
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	path = get_word(*line);
	*line += ft_strlen(path);
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	if (**line != '\n')
		ft_exit(INVALID_TEXTURES);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(strerror(errno));
	texture[cardinal].path = path;
	texture[cardinal].empty = false;
	texture[cardinal].texture = mlx_load_xpm42(path);
	printf("path: %s %s %p\n", mlx_strerror(mlx_errno), path, texture[cardinal].texture);
}