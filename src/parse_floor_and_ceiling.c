/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor_and_ceiling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:06:41 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/08 15:36:28 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	parse_rgb(t_allocated *tobfreed, char **rgb)
{
	int		nbr_of_elements;
	int		i;
	char	*ptr;

	i = 0;
	nbr_of_elements = 0;
	while (rgb[i])
	{
		ptr = rgb[i];
		if (ft_strncmp(ptr, "\n", 1) == 0)
			break ;
		while (*ptr)
		{
			if (*ptr == ' ' && check_spaces(&ptr) == -1)
				free_allocated_and_exit(tobfreed, true, false, INVALID_COLOR);
			if (!ft_isdigit(*ptr) && *ptr != '\n')
				free_allocated_and_exit(tobfreed, true, false, INVALID_COLOR);
			ptr++;
		}
		nbr_of_elements++;
		i++;
	}
	if (nbr_of_elements != 3)
		ft_exit(INVALID_COLOR);
}

void	get_rgb(t_allocated *tobfreed, char **line, void *floor_or_ceiling, char element)
{
	t_floor		*floor;
	t_ceiling	*ceiling;
	char		**rgb;

	rgb = ft_split_cub3d(tobfreed, *line, ',');
	tobfreed->var3 = rgb;
	parse_rgb(tobfreed, rgb);
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

void	parse_floor_and_ceiling(t_allocated *tobfreed, t_file *file, \
								char **line, char element)
{
	(*line)++;
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	if (element == 'F')
	{
		get_rgb(tobfreed, line, &file->floor, 'F');
		file->floor.empty = false;
	}
	else if (element == 'C')
	{
		get_rgb(tobfreed, line, &file->ceiling, 'C');
		file->ceiling.empty = false;
	}
}
