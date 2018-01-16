/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:35:16 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/16 16:23:32 by oantonen         ###   ########.fr       */
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
		if (*s == '\0' || specif(*s) != -1)
			break ;
		else
			s++;
	}
	return (s);
}

char	*browse_arg(char *arg, va_list ap)
{
	char	*sup_str;
	int		buf;
	void	*d;

	buf = 10000;
	sup_str = ft_strnew(10000);
	d = ap;
	while (*arg)
	{
		if (ft_strchr(arg, '%') == NULL)
		{
			// printf("\narg1=%s\n", arg);
			ft_strcat(&sup_str[g_mode.sup_len], arg);
			g_mode.sup_len += ft_strlen(arg);
			break ;
		}
		ft_memcpy(&sup_str[g_mode.sup_len], arg, ft_strchrlen(arg, '%'));
		g_mode.sup_len += ft_strchrlen(arg, '%');
		arg = ft_strchr(arg, '%');
		// printf("\narg2=%s\n", arg);
		arg = all_flags(++arg, ap);
		// printf("\narg3=%s\n", arg);
		if (*arg && ft_strchr("%cspdouxXCSOiDU", *arg) != NULL)
		{
			// printf("\narg4=%s\n", arg);
			d = va_arg(ap, void*);
			ft_memcpy(&sup_str[g_mode.sup_len], (*g_functions[specif(*arg)])(d), g_mode.cur_len);
			arg++;
			// printf("arg2=%s\n", arg);
		}
		// if (*arg && ft_strchr("%cspdouxXCSOiDU", *arg) == NULL)
			// arg++;
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
	// ft_putstr(super_str);
	printf_len = g_mode.sup_len;
	g_mode.sup_len = 0;
	return (printf_len);
}

//  int main()
// {
// 	// setlocale(LC_ALL, "");
// 	// i = ft_printf("str=%.5ls", L"");
	
// 	// ft_printf("my__begin=%+*.3d\n", -5, 42);
// 	// printf("lib_begin=%+*.3d\n", -5, 42);

// 	int i = ft_printf("@moulitest: %.o %.0o", 0, 0);
// 	printf("\ni=%d\n", i);
// 		i = printf("@moulitest: %.o %.0o", 0, 0);
// 	printf("\ni=%d\n", i);





// 	// printf("symbol %d\n", 123);
// }