/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:43:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/11 20:35:35 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

double		pf_float_sqrt(double sample, int g_prec)
{
	int		prec2;

	prec2 = g_prec;
	if (prec2 != 0)
		while (--prec2 != 0)
			sample = sample / 10;
	return (sample);
}

void	pf_float_output_nominus(char **s, size_t len, size_t bl, int sign)
{
	char 	*str_float;
	char	*tmp;
	char	c;

	c = (sign == 1) ? '-' : '\0';
	c = (ISPLUS == 1 && sign == 0) ? '+' : c;
	c = (ISSPACE == 1 && sign == 0 && ISPLUS == 0) ? ' ' : c;
	str_float = ft_strnew(bl);
	if (g_mode.width > len && ISZERO == 0)
		ft_memset(str_float, 32, bl - len);
	else if (g_mode.width > len && ISZERO == 1)
		ft_memset(str_float, 48, bl - len);
	if (g_mode.width > len && !ISZERO && c)
		str_float[bl - len - 1] = c;
	else if ((g_mode.width > len && ISZERO && c) || g_mode.width < len)
		str_float[0] = c;
	*s = ft_strcat(str_float, *s);
}

void	pf_float_output(char **s, size_t len, size_t bl, int sign)
{
	char 	*str_float;
	char	*tmp;

	if (ISMINUS == 1)
	{
		str_float = ft_strnew(bl);
		tmp = *s;
		(ISPLUS == 1 && sign == 0) ? str_float[0] = '+' : str_float[0];
		(sign == 1) ? str_float[0] = '-' : str_float[0];
		(!ISPLUS && sign == 0 && ISSPACE) ? str_float[0] = ' ' : str_float[0];
		*s = ft_strcat(str_float, *s);
		free(tmp);
		if (g_mode.width > len && ISZERO == 0)
			ft_memset(&str_float[len + 1], 32, bl - len - 1);
		else if (g_mode.width > len && ISZERO == 1)
			ft_memset(&str_float[len + 1], 48, bl - len - 1);
	}
	else
		pf_float_output_nominus(s, len, bl, sign);
}