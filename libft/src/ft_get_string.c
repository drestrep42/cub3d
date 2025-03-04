/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:47:38 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:09:13 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_get_string(char *s1, const char start, char end)
{
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != start && s1[i] != '\0' && s1[i] != '\n')
		i++;
	if (s1[i] == start)
	{
		while (s1[i] != end && s1[i] != '\0' && s1[i] != '\n')
		{
			i++;
			j++;
		}
		s2 = malloc((j + 2) * sizeof(char));
		i -= j;
		j = 0;
		while (s1[i] != end && s1[i] != '\0' && s1[i] != '\n')
			s2[j++] = s1[i++];
		s2[j] = s1[i];
		s2[j + 1] = '\0';
		return (s2);
	}
	return (NULL);
}
