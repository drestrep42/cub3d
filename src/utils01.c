/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:46:27 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/27 14:07:05 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (ft_strdup(line));
}

int	check_spaces(char **ptr)
{
	while (*ptr && **ptr == ' ')
		(*ptr)++;
	if (**ptr != '\n')
		return (-1);
	return (0);
}
