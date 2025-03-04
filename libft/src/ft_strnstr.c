/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:30:17 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:09:13 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (needle[i])
		i++;
	while (j < len && haystack[j] != '\0')
	{
		while (needle[k] && haystack[j + k] == needle[k] && j + k < len)
		{
			if (k + 1 == i)
				return ((char *)haystack + j);
			k++;
		}
		k = 0;
		j++;
	}
	return (NULL);
}
