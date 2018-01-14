/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ptr.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:04:37 by oantonen          #+#    #+#             */
/*   Updated: 2018/01/12 16:47:22 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_PTR_H
# define FUNC_PTR_H

# include "hprintf.h"

char* (*g_functions[])() = {
	pf_percent,
	pf_putchar, 
	pf_putstr, 
	pf_putaddr, 
	pf_put_signed_nb,
	pf_put_unsigned_nb, 
	pf_put_unsigned_nb, 
	pf_put_unsigned_nb,
	pf_put_unsigned_nb,
	// pf_float_f,
	// pf_float_f,

};

// 1	c	pf_putchar, 
// 2	s	pf_putstr, 
// 3	p	pf_putaddr, 
// 4	d	pf_put_signed_nb,
// 5	o	pf_put_unsigned_nb, 
// 6	u	pf_put_unsigned_nb, 
// 7	x	pf_put_unsigned_nb,
// 8	X	pf_put_unsigned_nb,
// 9	f	pf_float_f_fraction,
// 10	F	pf_float_f_fraction,

#endif