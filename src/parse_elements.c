/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:04:56 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/06 20:03:48 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_texture(t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (mlx->file.textures[i].xpm)
		{
			free(mlx->file.textures[i].path);
			mlx_delete_texture(&mlx->file.textures[i].xpm->texture);
			mlx->file.textures[i].xpm = NULL;
		}
	}
}

void	free_error(t_mlx *mlx, char *word, char *line)
{
	free(word);
	free(line);
	free_texture(mlx);
	ft_exit(INVALID_TEXTURES);
}

void	parse_each_element(t_mlx *mlx, t_file *file, char **line)
{
	char	*word;
	int		i;

	i = 0;
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\t')
		i++;
	word = ft_substr(*line, 0, i);
	if (file->textures[NO].empty && ft_strncmp(word, "NO", 2) == 0)
		parse_textures(file->textures, NO, line, word);
	else if (file->textures[SO].empty && ft_strncmp(word, "SO", 2) == 0)
		parse_textures(file->textures, SO, line, word);
	else if (file->textures[EA].empty && ft_strncmp(word, "EA", 2) == 0)
		parse_textures(file->textures, EA, line, word);
	else if (file->textures[WE].empty && ft_strncmp(word, "WE", 2) == 0)
		parse_textures(file->textures, WE, line, word);
	else if (file->floor.empty && ft_strncmp(word, "F", 2) == 0)
		parse_floor_and_ceiling(&file->floor, &file->ceiling, line, 'F');
	else if (file->ceiling.empty && ft_strncmp(word, "C", 2) == 0)
		parse_floor_and_ceiling(&file->floor, &file->ceiling, line, 'C');
	else if (ft_strncmp(word, "\n", 1) != 0)
		free_error(mlx, word, *line);
	free(word);
}

void	parse_space(char *line, char *trimmed, int fd)
{
	while (line)
	{
		trimmed = line;
		while (*trimmed == ' ')
			trimmed++;
		if (*trimmed != '\n' && !ft_isdigit(*trimmed))
		{
			free(line);
			ft_exit(INVALID_TEXTURES);
		}
		if (ft_isdigit(*trimmed))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	parse_elements(t_mlx *mlx, t_file *file, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	if (!line)
		ft_exit(EMPTY_MAP);
	while (line && (file->textures[NO].empty || file->textures[SO].empty \
			|| file->textures[EA].empty || file->textures[WE].empty \
			|| file->floor.empty || file->ceiling.empty))
	{
		trimmed = skip_spaces(line);
		free(line);
		line = trimmed;
		parse_each_element(mlx, file, &trimmed);
		free(line);
		line = get_next_line(fd);
	}
	parse_space(line, trimmed, fd);
}
