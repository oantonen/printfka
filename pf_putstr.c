/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 19:13:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/19 12:54:01 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*ft_flag_width(char *str, int len, int width)
{
	char	*tmp;
// printf("str=%s\n", str);
// printf("len1=%d\n", len);
	tmp = ft_strcpy(ft_strnew(len), str);
	if (width > len && ISMINUS == 0)
	{
		str = ft_strnew(width);
		if (ISZERO == 0)
			str = ft_memset(str, ' ', width - len);
		else
			str = ft_memset(str, '0', width - len);
		str = ft_strcat(str, tmp);

	}
	else if (width > len && ISMINUS == 1)
	{
		str = ft_strnew(width);
		str = ft_memset(str, ' ', width);
		str = ft_memcpy(str, tmp, len);
	}
	ft_strdel(&tmp);
	len = (ft_strchr("cC", g_mode.specif) && width > 1) ? width : len;
	g_mode.sup_len += (ft_strchr("cC", g_mode.specif)) ? len : ft_strlen(str);
	g_mode.cur_len = (ft_strchr("cC", g_mode.specif)) ? len : ft_strlen(str);
// printf("len2=%d\n", len);
// printf("g_mode.cur_len=%d\n", g_mode.cur_len);
// printf("g_mode.sup_len=%d\n", g_mode.sup_len);
	return (str);
}

char	*ft_str_unic(char *str, unsigned int *s)
{
	char *tmp;
	char *pchar;

	tmp = NULL;
	pchar = NULL;
	if (ISDOT == 0)
		while (*s)
		{
			tmp = str;
			pchar = pf_putchar(*s++);
			str = ft_strjoin(str, pchar);
			ft_strdel(&tmp);
			ft_strdel(&pchar);
		}
	else if (ISDOT == 1 && g_mode.prec)
		while (*s && g_mode.prec / ft_strlen(pf_putchar(*s)))
		{
			tmp = str;
			g_mode.prec = g_mode.prec - ft_strlen(pf_putchar(*s));
			str = ft_strjoin(str, pf_putchar(*s));
			s++;
			ft_strdel(&tmp);
		}
	else if (ISDOT == 1 && g_mode.prec == 0)
		return (str);
	return (str);
}

char	*pf_putstr(va_list ap)
{
	char			*str;
	unsigned int	*s;

	str = NULL;
	s = va_arg(ap, unsigned int*);
	if (s)
	{
		if (ISL == 0)
		{
			str = ft_strnew(ft_strlen((const char*)s));
			if (ISDOT == 0 || (ISDOT && g_mode.prec < 0))
				str = ft_strcpy(str, (const char*)s);
			else if (ISDOT == 1 && g_mode.prec > 0)
				str = ft_strncpy(str, (const char*)s, g_mode.prec);
		}
		else
			str = ft_str_unic(ft_strnew(0), s);
	}
	else if (s == NULL && ISDOT)
		str = ft_strncpy(ft_strnew(6), "(null)", g_mode.prec);
	else
		str = ft_strcpy(ft_strnew(6), "(null)");
	// if ((ISL && g_mode.specif == 's') && MB_CUR_MAX == 1)
		// exit(0);
	return (ft_flag_width(str, ft_strlen(str), g_mode.width));
}
