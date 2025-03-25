/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:46:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/25 17:47:45 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (ft_strdup(line));
}

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

int	check_spaces(char **ptr)
{
	while (*ptr && **ptr == ' ')
		(*ptr)++;
	if (**ptr != '\n')
		return (-1);
	return (0);
}
