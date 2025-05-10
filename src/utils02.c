/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:52:50 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/10 21:09:45 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_countstr(t_allocated *tobfreed, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	flags_init(tobfreed, false, true, true);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] == c)
			free_alloc_and_exit(tobfreed, tobfreed->flags, INVALID_COLOR);
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	if (j != 2)
		free_alloc_and_exit(tobfreed, tobfreed->flags, INVALID_COLOR);
	if (s[0] != c)
		j++;
	return (j);
}

char	*ft_string(const char *s, char c, size_t counter)
{
	char	*str;
	size_t	i;

	i = counter;
	while (s[i] != c && s[i] != '\0')
		i++;
	str = malloc(sizeof(char) * i + 1 - counter);
	if (!str || !s)
		return (NULL);
	i = 0;
	while (s[counter] != c && s[counter] != '\0')
	{
		str[i] = s[counter];
		i++;
		counter++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_cub3d(t_allocated *tobfreed, char const *s, char c)
{
	char	**new;
	size_t	sn;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	sn = ft_countstr(tobfreed, s, c);
	new = malloc((sn + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (j < sn)
	{
		while (s[i] == c && s[i])
			i++;
		new[j] = ft_string(s, c, i);
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	new[j] = NULL;
	return (new);
}

double	safe_div(double num, double den)
{
	double	eps;

	eps = 1e-6;
	if (fabs(den) < eps)
	{
		if (den < 0)
			return (num / -eps);
		else
			return (num / eps);
	}
	else
		return (num / den);
}
