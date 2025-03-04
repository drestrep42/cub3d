/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 07:51:41 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:12:44 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putptr(size_t ptr, int *len)
{
	size_t	i;
	char	aux[25];
	char	*base;

	i = 0;
	base = "0123456789abcdef";
	write (1, "0x", 2);
	(*len) += 2;
	if (ptr == 0)
	{
		ft_putchar('0', len);
		return ;
	}
	while (ptr != 0)
	{
		aux[i++] = base[ptr % 16];
		ptr = ptr / 16;
		while (ptr == 0 && i--)
		{
			write (1, &aux[i], 1);
			(*len)++;
		}
	}
}
