/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_flag_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 15:22:35 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/12 14:16:04 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*ft_flag_width(char *str)
{
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	tmp = str;
	if (g_mode.width > len && ISMINUS == 0)
	{
		str = ft_strnew(g_mode.width);
		str = ft_memset(str, ' ', g_mode.width - len);
		ft_strcat(str, tmp);
	}
	else if (g_mode.width > len && ISMINUS == 1)
	{
		str = ft_strnew(g_mode.width);
		str = ft_memset(str, ' ', g_mode.width);
		str = ft_memcpy(str, tmp, len);
	}
	free(tmp);
	tmp = NULL;
	return (str);
}