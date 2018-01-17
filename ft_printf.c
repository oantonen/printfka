/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:35:16 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/17 21:43:23 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"
#include "func_ptr.h"
#include <locale.h>
#include <limits.h>

int		isdigit_spec(char s)
{
	char	*dig;

	dig = "123456789"; // 0 ???
	while (*dig != s && *dig)
		dig++;
	return ((*dig == s) ? TRUE : FALSE);
}

char	*all_flags(char *s, va_list ap)
{
	g_mode.flags = 0;
	g_mode.prec = 0;
	g_mode.width = 0;
	g_mode.specif = 0;
	while (*s && specif(*s) == -1)
	{
		// printf("s=%c\n", *s);
		(*s == '-') ? MINUS : *s;
		(*s == '+') ? PLUS : *s;
		(*s == ' ') ? SPACE : *s;
		(*s == '#') ? HASH : *s;
		(*s == '0') ? ZERO : *s;
		(isdigit_spec(*s) == 1) ? g_mode.width = pf_get_num(&s) : *s;
		(*s == '*') ? g_mode.width = va_arg(ap, int) : *s;
		(g_mode.width < 0) ? MINUS : 0;
		(g_mode.width < 0) ? g_mode.width *= -1 : g_mode.width;
		if (*s == '.')
		{
			DOT;
			s++;
			g_mode.prec = pf_get_num(&s);
			(*s++ == '*') ? g_mode.prec = va_arg(ap, int) : *s--;
		}
		if (*s == 'h' && *(s + 1) != 'h') // доработать, чтобы не заходило
			H;
		if (*s == 'h' && *(s + 1) == 'h') // (s + 2) = segfault
		{
			s++;
			HH;
		}
		(*s == 'l' && *(s + 1) != 'l') ? L : *s;
		(*s == 'l' && *(s + 1) == 'l') ? LL : *s;
		(*s == 'l' && *(s + 1) == 'l') ? s = s + 1 : s;
		(*s == 'j') ? J : *s;
		(*s == 'z') ? Z : *s;
		(*s == '\'') ? APOSTROPHE : *s;
		(*s == 'L') ? LD : *s;
		// printf("s=%c\n", *s);
		if (*s == '\0' || specif(*s) != -1 || !ft_strchr(" -+#*hljz\'.01234567890", *s))
			break ;
		else
			s++;
	}
	return (s);
}

char	*browse_arg(char *arg, va_list ap)
{
	char	*sup_str;
	char	*clr;

	sup_str = ft_strnew(1000);
	while (*arg)
	{
		if (ft_strchr(arg, '%') == NULL)
		{
			// printf("\narg1=%s\n", arg);
			ft_strcat(&sup_str[g_mode.sup_len], arg);
			g_mode.sup_len += ft_strlen(arg);
			break ;
		}
		ft_memcpy(&sup_str[g_mode.sup_len], arg, ft_strchrlen(arg, '%')); //допилить добавку памяти
		g_mode.sup_len += ft_strchrlen(arg, '%');
		arg = ft_strchr(arg, '%');
		// printf("\narg2=%s\n", arg);
		arg = all_flags(++arg, ap);
		// printf("\narg3=%s\n", arg);
		if (*arg && ft_strchr("%cspdouxXCSOiDU", *arg) != NULL)
		{
			// printf("\narg4=%s\n", arg);
			clr = pf_function_call(*arg, ap);
			// ft_memcpy(&sup_str[g_mode.sup_len], pf_function_call(*arg, ap), g_mode.cur_len);
			ft_strncat(sup_str, clr, g_mode.cur_len);
			// printf("g_mode.cur_len=%d\n", g_mode.cur_len);
			if (ft_strchr("%pDuUxXoOdi", *arg))
				ft_strdel(&clr);
			arg++;
			// printf("arg2=%s\n", arg);
		}
	}
	return (sup_str);
}


int		ft_printf(const char *arg, ...)
{
	va_list		ap;
	char		*super_str;
	int			printf_len;

	va_start(ap, arg);
	super_str = browse_arg((char*)arg, ap);
	va_end(ap);
	write(1, super_str, g_mode.sup_len);
	// ft_memset(super_str, 0, 1000);
	// ft_strdel(&super_str);
	printf_len = g_mode.sup_len;
	g_mode.sup_len = 0;
	return (printf_len);
}
