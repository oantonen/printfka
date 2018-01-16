/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_mng.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:09:36 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/16 15:14:13 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*pf_apply_flags_nominus(char *s, int len_old, int len_new, char *pref)
{
	char	*new_s;
	int		p;

	p = ft_strlen(pref);
// printf("len_old=%d\n", len_old);
// printf("len_new=%d\n", len_new);

	new_s = ft_strnew(len_new);
	if (g_mode.width > len_old)
		ft_memset(new_s, 32, len_new - len_old);
	if (g_mode.width > len_old && ISZERO == 1 && ISDOT == 0)
		ft_memset(new_s, 48, len_new - len_old);
	else if (g_mode.width > len_old && ISZERO == 1 && ISDOT == 1)
		ft_memset(new_s, 48, len_new - len_old);
	// if (g_mode.width > len_old && !ISZERO && c)
		// new_s[len_new - len_old - 1] = (c && !ft_strchr("xXo", g_mode.specif)) ? c : new_s[0];
	// else if ((g_mode.width > len_old && ISZERO && c) || g_mode.width < len_old)
		// new_s[0] = (c && !ft_strchr("xXo", g_mode.specif)) ? c : new_s[0];
	if (g_mode.width > len_old && !ISZERO && *pref)
		ft_strncpy(&new_s[len_new - len_old - p], pref, p);
	else if ((g_mode.width > len_old && ISZERO && *pref) || g_mode.width < len_old)
		ft_strncpy(new_s, pref, p);
	ft_strcat(new_s, s);
	g_mode.sup_len += ft_strlen(new_s);
	g_mode.cur_len = ft_strlen(new_s);
	// printf("g_mode.sup_len=%d\n", g_mode.sup_len);
	// printf("g_mode.cur_len=%d\n", g_mode.cur_len);
	return (new_s);
}

char	*pf_apply_flags(char *s, int len_old, int len_new, int sign, char *pref)
{
	char	*new_s;
	char	c;
	int		p;

// printf("len_old=%d\n", len_old);
// printf("len_new=%d\n", len_new);
	c = (sign == -1 && g_mode.specif == 'd') ? '-' : '\0';
	c = (ISPLUS == 1 && sign == 1 && g_mode.specif == 'd') ? '+' : c;
	c = (ISSPACE && sign != -1 && !ISPLUS && g_mode.specif == 'd') ? ' ' : c;
	p = ft_strlen(pref);
	if (ISMINUS == 1)
	{
		new_s = ft_strnew(len_new);
		// new_s[0] = (c && !ft_strchr("xXo", g_mode.specif)) ? c : new_s[0];
		ft_strcpy(new_s, pref);
		ft_strcat(new_s, s);
		if (g_mode.width > len_old && *pref) // g_mode.prec заменить на len_old
			ft_memset(&new_s[len_old + p], 32, len_new - len_old - p);
		else if (g_mode.width > len_old && !(*pref))
			ft_memset(&new_s[len_old], 32, len_new - len_old);
		g_mode.sup_len += ft_strlen(new_s);
		g_mode.cur_len = ft_strlen(new_s);
		// printf("g_mode.sup_len=%d\n", g_mode.sup_len);
		// printf("g_mode.cur_len=%d\n", g_mode.cur_len);
	}
	else 
		new_s = pf_apply_flags_nominus(s, len_old, len_new, pref);
	return (new_s);
}

char	*pf_final_modify(char *s, int len_old, int width, char *pref)
{
	int		len_new;
	char	*new_s;
	int		sign = 0;
// printf("s=%s\n", s);
	len_new = 0;
// sign = ((int)nb >= 0) ? 1 : -1;
	(width < 0) ? MINUS : width;
	(width < 0) ? width *= -1 : width;
	if (ISSPACE == 1 && ISPLUS == 0 && width == 0 && pref[0] == '-')
		len_new++;
	if (sign == -1 && width <= len_old)
		len_new++;
	if (ISHASH && ft_strchr("xX", g_mode.specif) && g_mode.width < len_old)
		len_new += 2;
	if (width > len_old && width >= g_mode.prec)
		len_new += width;
	else if (g_mode.prec > len_old && width <= g_mode.prec)
		len_new += g_mode.prec;
	else if (width <= len_old && len_old >= g_mode.prec)
		len_new += len_old;
	if (ISPLUS && sign == 1 && g_mode.specif == 'd' && width < len_new)
		len_new++;
	new_s = pf_apply_flags(s, len_old, len_new, sign, pref);
	return (new_s);
}

// void	pf_output_nominus(char **s, size_t len, size_t bl, int sign)
// {
// 	char 	*str_float;
// 	char	*tmp;
// 	char	c;

// 	c = (sign == 1) ? '-' : '\0';
// 	c = (ISPLUS == 1 && sign == 0) ? '+' : c;
// 	c = (ISSPACE == 1 && sign == 0 && ISPLUS == 0) ? ' ' : c;
// 	str_float = ft_strnew(bl);
// 	if (g_mode.width > len && ISZERO == 0)
// 		ft_memset(str_float, 32, bl - len);
// 	else if (g_mode.width > len && ISZERO == 1)
// 		ft_memset(str_float, 48, bl - len);
// 	if (g_mode.width > len && !ISZERO && c)
// 		str_float[bl - len - 1] = c;
// 	else if ((g_mode.width > len && ISZERO && c) || g_mode.width < len)
// 		str_float[0] = c;
// 	*s = ft_strcat(str_float, *s);
// }

// void	pf_output(char **s, size_t len, size_t bl, int sign)
// {
// 	char 	*str_float;
// 	char	*tmp;

// 	if (ISMINUS == 1)
// 	{
// 		str_float = ft_strnew(bl);
// 		tmp = *s;
// 		(ISPLUS == 1 && sign == 0) ? str_float[0] = '+' : str_float[0];
// 		(sign == 1) ? str_float[0] = '-' : str_float[0];
// 		(!ISPLUS && sign == 0 && ISSPACE) ? str_float[0] = ' ' : str_float[0];
// 		*s = ft_strcat(str_float, *s);
// 		free(tmp);
// 		if (g_mode.width > len && ISZERO == 0)
// 			ft_memset(&str_float[len + 1], 32, bl - len - 1);
// 		else if (g_mode.width > len && ISZERO == 1)
// 			ft_memset(&str_float[len + 1], 48, bl - len - 1);
// 	}
// 	else
// 		pf_output_nominus(s, len, bl, sign);
// }