/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 10:50:50 by oantonen          #+#    #+#             */
/*   Updated: 2017/11/22 20:29:27 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		char2int(char str)
{
	char	*base;
	int		i;

	i = 0;
	base = "0123456789ABCDEF";
	if ((str >= '0' && str <= '9') || (str >= 'A' && str <= 'F'))
		while (base[i] != str)
			i++;
	return (i);
}

static	char	checkchar(char str, int s_base)
{
	char	*base;
	int		i;

	base = "0123456789ABCDEF";
	i = 0;
	while (*base && i < s_base)
	{
		if (str == *base)
			return (1);
		base++;
		i++;
	}
	return (0);
}

size_t			ft_atoi_base(const char *str, int s_base)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	(*str == '-' && s_base == 10) ? sign = -1 : sign;
	(*str == '+' || *str == '-') ? str++ : str;
	while (checkchar(ft_toupper(*str), s_base) == 1 && *str)
	{
		res = res * s_base + (char2int(ft_toupper(*str)) % s_base);
		str++;
	}
	return (res * sign);
}
