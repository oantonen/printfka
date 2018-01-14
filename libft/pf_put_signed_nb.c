/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_put_signed_nb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 16:44:15 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/14 20:58:52 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char		*pf_arr_length(long long int nb, int *chars, int prec)
{
	int		i;
	int		nb2;
	char	*fresh;

	i = 0;
	nb2 = nb;
	(nb == 0 && !ISDOT) ? i++ : i;
	nb = (nb <= 0) ? -nb : nb;
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	nb = nb2;
	*chars = i;
	if (MB_CUR_MAX == 4 && ISAPOSTROPHE == 1)
	{
		((i > 3 && nb > 0) || (i > 4 && nb < 0)) ? *chars += (i / 3) : *chars;
		*chars = (i % 3 == 0 && i > 3) ? *chars - 1 : *chars;
	}
	*chars += (prec > i) ? prec - i : 0;
	fresh = ft_strnew(*chars);
	ft_memset(fresh, '0', *chars);
	// printf("chars=%d\n", *chars);
	return (fresh);
}

char		*pf_itoa_signed(long long int nb)
{
	char		*fresh;
	int			chars;
	int			i;
	uintmax_t	nb2;

	i = 0;
	nb2 = (nb < 0) ? -nb : nb;
	fresh = pf_arr_length(nb, &chars, g_mode.prec);
	(nb == 0 && !ISDOT) ? fresh[0] = '0' : fresh[0];
	if (nb == 0)
		return (fresh);
	while (nb2 != 0)
	{
		if (MB_CUR_MAX == 4 && ISAPOSTROPHE == 1 && i != 0 && (i % 3) == 0)
			fresh[--chars] = ',';
		i++;
		fresh[--chars] = nb2 % 10 + '0';
		nb2 = nb2 / 10;
	}
	return (fresh);
}

intmax_t	cast_ssize(void *nb)
{
	if (ISHH == 1 && !((g_mode.flags << 20) >> 27))
		return ((signed char)nb);
	else if (ISH == 1 && !((g_mode.flags << 20) >> 28))
		return ((short)nb);
	else if (ISL == 1 && !((g_mode.flags << 20) >> 29))
		return ((long)nb);
	else if (ISLL == 1 && !((g_mode.flags << 20) >> 30))
		return ((long long)nb);
	else if (ISJ == 1 && !((g_mode.flags << 20) >> 31))
		return ((intmax_t)nb);
	else if (ISZ)
		return ((ssize_t)nb);
	return ((int)nb);
}

char		*pf_put_signed_nb(void *nb)
{
	char	*s;
	char	*pref;
	int		len_new;
	int		len_old;

	len_new = 0;
	s = pf_itoa_signed(cast_ssize(nb));
	len_old = ft_strlen(s);
	pref = (ISPLUS && cast_ssize(nb) >= 0) ? "+" : "";
	pref = (ISSPACE && cast_ssize(nb) > 0 && !ISPLUS) ? " " : pref;
	pref = (cast_ssize(nb) < 0) ? "-" : pref;
	return (pf_final_modify(s, len_old, g_mode.width, pref));
}



