/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 04:41:47 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:12:48 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putnbr(int nbr, int *len)
{
	long int	i;

	i = nbr;
	if (nbr == -2147483648)
	{
		write (1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	if (i < 0)
	{
		write(1, "-", 1);
		(*len)++;
		ft_putnbr(i * -1, len);
	}
	else
	{
		if (i > 9)
			ft_putnbr(i / 10, len);
		ft_putchar(i % 10 + '0', len);
	}
}
