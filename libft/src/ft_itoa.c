/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:11:31 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:09:13 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_str(long aux, long size, long n1, int n)
{
	char	*str;

	str = (char *) malloc(size + 1 * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > 0 && n >= 0)
	{
		aux = n1 % 10;
		n1 = n1 / 10;
		str[--size] = aux + '0';
	}
	while (size > 1 && n < 0)
	{
		str[0] = '-';
		aux = n1 % 10;
		n1 = n1 / 10;
		str[--size] = aux + '0';
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	size;
	long	aux;
	long	n1;

	size = 1;
	aux = (long)n;
	if (aux < 0)
	{
		aux *= -1;
		size++;
	}
	n1 = aux;
	while (aux >= 10)
	{
		aux = aux / 10;
		size++;
	}
	str = ft_str(aux, size, n1, n);
	return (str);
}
