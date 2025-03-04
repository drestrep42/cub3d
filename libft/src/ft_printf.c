/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:02:54 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:12:54 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_printf(char const *str, ...)
{
	int		i;
	int		len;
	va_list	ap;

	i = 0;
	len = 0;
	va_start (ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			ft_datatype(ap, str[i], &len, &i);
			i++;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
			len++;
		}
	}
	va_end (ap);
	return (len);
}

void	ft_datatype(va_list list, char c, int *len, int *i)
{
	if (c == 'c')
		ft_putchar(va_arg(list, int), len);
	else if (c == 's')
		ft_putstr(va_arg(list, char *), len);
	else if (c == 'p')
		ft_putptr(va_arg(list, size_t), len);
	else if (c == 'i' || c == 'd' )
		ft_putnbr(va_arg(list, int), len);
	else if (c == 'u')
		ft_unsigned_int(va_arg(list, int), len);
	else if (c == 'x')
		ft_hexadecimal(va_arg(list, unsigned int), len, 'x');
	else if (c == 'X')
		ft_hexadecimal(va_arg(list, unsigned int), len, 'X');
	else if (c == '%')
		ft_putchar('%', len);
	else
		(*i)--;
}
