/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 14:23:21 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/17 21:55:17 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

int		char_count(uintmax_t value, int base)
{
	int i;

	i = 0;
	if (value == 0 && !ISDOT)
		return (1);
	while (value)
	{
		value = value / base;
		i++;
	}
	return (i);
}

char			*pf_itoa_addr(char *res, uintmax_t value, int base, int count)
{
	char		*base_num;

	base_num = "0123456789abcdef";
	if (value == 0 && !ISDOT)
		res[2] = '0';
	while (value != 0 )
	{
		if (value % base > 9)
			res[count - 1] = base_num[value % base];
		else
			res[count - 1] = value % base + '0';
		value = value / base;
		count--;
	}
	// g_mode.sup_len += ft_strlen(res);
	// g_mode.cur_len = ft_strlen(res);
	return (pf_final_modify(res, count, g_mode.width, ""));
}

char	*pf_putaddr(va_list ap)
{
	char		*res;
	int			count;
	uintmax_t	adr;

	adr = va_arg(ap, uintmax_t);
	count = char_count(adr, 16) + 2;

	res = ft_strnew(count);
	res[0] = '0';
	res[1] = 'x';
	return (pf_itoa_addr(res, adr, 16, count));
}
