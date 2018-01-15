/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:35:16 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/15 14:14:37 by oantonen         ###   ########.fr       */
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

	buf = 100;
	sup_str = ft_strnew(100);
	while (*arg)
	{
		if (ft_strchr(arg, '%') == NULL)
		{
			// printf("\narg1=%s\n", arg);
			sup_str = ft_strcat(sup_str, arg);
			break ;
		}
		sup_str = ft_strncat(sup_str, arg, ft_strchrlen(arg, '%')); //допилить добавку памяти
		arg = ft_strchr(arg, '%');
		arg = all_flags(++arg, ap);
		// printf("\narg2=%s\n", arg);
		if (ft_strchr("%cspdouxXCSOiDU", *arg) != NULL)
		{
			// printf("\narg2=%s\n", arg);
			d = va_arg(ap, void*);
			sup_str = add_mem(sup_str, (*g_functions[specif(*arg)])(d), &buf);
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

	va_start(ap, arg);
	super_str = browse_arg((char*)arg, ap);
	va_end(ap);
	ft_putstr(super_str);
	return (ft_strlen(super_str));
}

//  int main()
// {
// 	// setlocale(LC_ALL, "");
// 	// i = ft_printf("str=%.5ls", L"");
	
// 	// ft_printf("my__begin=%+*.3d\n", -5, 42);
// 	// printf("lib_begin=%+*.3d\n", -5, 42);

// 	int i = ft_printf("my__begin=%.4o", 42);
// 	printf("\ni=%d\n", i);
// 		i = printf("lib_begin=%.4o", 42);
// 	printf("\ni=%d\n", i);





// 	// printf("symbol %d\n", 123);
// }