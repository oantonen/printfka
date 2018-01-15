/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:07:44 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/15 14:36:26 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hprintf.h"

char	*pf_percent(void *nb)
{
	char	*str;
	int		len;

	str = NULL;
	nb = NULL;
	len = (g_mode.width > 1) ? g_mode.width : 1;
	str = ft_strnew(len);
	if (ISMINUS)
	{
		ft_memset(str, ' ', len);
		str[0] = '%';		
	}
	else
	{
		if (ISZERO == 1)
			ft_memset(str, '0', len);
		else
			ft_memset(str, ' ', len);
		str[len - 1] = '%';		
	}
	return (str);
}