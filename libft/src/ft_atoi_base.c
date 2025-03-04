/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:38:31 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:09:17 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	hex_to_decimal(char hex)
{
	if (hex >= '0' && hex <= '9')
		return (hex - '0');
	else if (hex >= 'A' && hex <= 'F')
		return (hex - 'A' + 10);
	else if (hex >= 'a' && hex <= 'f')
		return (hex - 'a' + 10);
	else
		return (-1);
}

int	ft_atoi_base(char *str)
{
	int	number;
	int	digit;
	int	i;

	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '0' && str[i + 1] == 'x')
		i += 2;
	while (str[i] != '\0' && str[i] != '\n')
	{
		digit = hex_to_decimal(str[i]);
		if (digit == -1)
		{
			ft_printf("%s wrong hex value, %c", str, str[i]);
			exit(1);
		}
		number = number * 16 + digit;
		i++;
	}
	return (number);
}
