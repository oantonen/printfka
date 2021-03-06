/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 11:44:07 by oantonen          #+#    #+#             */
/*   Updated: 2017/12/24 15:50:13 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strchrlen(char *str, char c)
{
	int	len;

	len = 0;
	while (str && *str && *str != c)
	{
		str++;
		len++;
	}
	return (len);
}
