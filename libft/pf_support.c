/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_support.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 17:26:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/14 15:58:43 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*add_mem(char *super_str, char *result, int *buf)
{
	int		add;
	char	*tmp;
	int		size_sup;

	tmp = super_str;
	size_sup = ft_strlen(super_str);
	size_sup = *buf - size_sup;
	add = ft_strlcat(super_str, result, *buf);
	if (add > *buf)
	{
		*buf = add * 2;
		super_str = ft_strnew(*buf);
		ft_strcpy(super_str, tmp); // копирование '\0' ??? strlen, strcpy...
		ft_strcat(super_str, &result[size_sup - 1]);
		ft_strdel(&tmp);
	}
	return (super_str);
}

int		specif(char s)
{
	char	*convers;
	char	*ptr;

	// convers[ft_strchr(convers, s) - ptr]
	convers = "%cspdouxXCSOiDU";
	ptr = convers;
	if (ft_strchr("CSDOU", s))
	{
		L;
		s = s + 32;
	}
	(s == 'i') ? s = 'd' : s;
	if ((ft_strchr(convers, s)))
		g_mode.specif = convers[ft_strchr(convers, s) - ptr];
	while (*convers)
	{
		if (*convers == s)
			return (convers - ptr);
		convers++;
	}
	return (-1);
}

int		pf_get_num(char **str)
{
	int		res;
	char	symb;

	res = 0;
	symb = **str;
	while (ft_isdigit(**str) && **str)
	{
		res = res * 10 + (symb - 48);
		symb = *(++*str);		
	}
	// printf("res=%d\n", res);
	return (res);
}
