/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:33:01 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:12:15 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_unsigned_int(int var, int *len)
{
	unsigned int	i;
	char			*base;

	i = (unsigned int)var;
	base = "0123456789";
	if (i > 9)
	{
		ft_unsigned_int(i / 10, len);
		i = i % 10;
	}
	ft_putchar(base[i], len);
}
