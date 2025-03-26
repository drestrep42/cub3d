/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:48 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/25 17:45:24 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	parse_rgb(char **rgb)
{
	int		nbr_of_elements;
	char	*ptr;

	nbr_of_elements = 0;
	while (*rgb)
	{
		ptr = *rgb;
		if (ft_strncmp(ptr, "\n", 1) == 0)
			break ;
		while (*ptr)
		{
			if (*ptr == ' ' && check_spaces(&ptr) == -1)
				ft_exit(INVALID_TEXTURES);
			if (!ft_isdigit(*ptr) && *ptr != '\n')
				ft_exit(INVALID_TEXTURES);
			ptr++;
		}
		nbr_of_elements++;
		rgb++;
	}
	if (nbr_of_elements != 3)
		ft_exit(INVALID_TEXTURES);
}

void	get_rgb(char **line, void *floor_or_ceiling, char element)
{
	t_floor		*floor;
	t_ceiling	*ceiling;
	char		**rgb;

	rgb = ft_split_cub3d(*line, ',');
	parse_rgb(rgb);
	if (element == 'F')
	{
		floor = (t_floor *)floor_or_ceiling;
		floor->color[R] = ft_atoi(rgb[R]);
		floor->color[G] = ft_atoi(rgb[G]);
		floor->color[B] = ft_atoi(rgb[B]);
	}
	else if (element == 'C')
	{
		ceiling = (t_ceiling *)floor_or_ceiling;
		ceiling->color[R] = ft_atoi(rgb[R]);
		ceiling->color[G] = ft_atoi(rgb[G]);
		ceiling->color[B] = ft_atoi(rgb[B]);
	}
	free(rgb[R]);
	free(rgb[G]);
	free(rgb[B]);
	free(rgb);
}

void	parse_floor_and_ceiling(t_floor *floor, t_ceiling *ceiling, \
								char **line, char element)
{
	(*line)++;
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	if (element == 'F')
	{
		get_rgb(line, floor, 'F');
		(*floor).empty = false;
	}
	else if (element == 'C')
	{
		get_rgb(line, ceiling, 'C');
		(*ceiling).empty = false;
	}
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
}
