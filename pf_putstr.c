/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 19:13:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/15 21:37:31 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*ft_flag_width(char *str, int len)
{
	char	*tmp;
// printf("str=%s\n", str);
// printf("len=%d\n", len);
	tmp = str;
	if (g_mode.width > len && ISMINUS == 0)
	{
		str = ft_strnew(g_mode.width);
		if (ISZERO == 0)
			str = ft_memset(str, ' ', g_mode.width - len);
		else
			str = ft_memset(str, '0', g_mode.width - len);
		str = ft_strcat(str, tmp);

	}
	else if (g_mode.width > len && ISMINUS == 1)
	{
		str = ft_strnew(g_mode.width);
		str = ft_memset(str, ' ', g_mode.width);
		str = ft_memcpy(str, tmp, len);
	}
	if (ft_strcmp(tmp, "(null)") != 0)
		ft_strdel(&tmp);
	len = (g_mode.specif == 'c' && g_mode.width > 1) ? g_mode.width : len;
	g_mode.sup_len += (g_mode.specif == 'c') ? len : ft_strlen(str);
	g_mode.cur_len = (g_mode.specif == 'c') ? len : ft_strlen(str);
	return (str);
}

char	*ft_str_unic(char *str, unsigned int *s)
{
	if (ISDOT == 0)
		while (*s)
			str = ft_strcat(str, pf_putchar(*s++));
	else if (ISDOT == 1 && g_mode.prec)
		while (*s && g_mode.prec/ft_strlen(pf_putchar(*s)))
		{
			g_mode.prec = g_mode.prec - ft_strlen(pf_putchar(*s));
			str = ft_strcat(str, pf_putchar(*s++));
		}
	else if (ISDOT == 1 && g_mode.prec == 0)
		str = "";
	return (str);
}

char	*pf_putstr(unsigned int *s)
{
	char	*str;
	int		len;

	// len = ft_strlen((const char*)s);
	if ((char*)s)
	{
		len = ft_strlen((const char*)s);
		str = ft_strnew(len);
		if (ISL == 0)
		{
			if (ISDOT == 0)
				str = ft_strcpy(str, (const char*)s);
			else
				str = ft_strncpy(str, (const char*)s, g_mode.prec);
		}
		else
			ft_str_unic(str, s);
	}
	else
		str = "(null)";
	len = ft_strlen(str);
	return (ft_flag_width(str, len));
}
