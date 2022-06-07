/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:02:44 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/14 19:21:52 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long long	process_decimal(t_arg_info *arg)
{
	unsigned long long	u;
	long int			d;

	d = va_arg(arg->ap, int);
	if (d >= 0)
	{
		if (prnt_check_flag(arg, FLAG_PLUS))
			arg->print_sign = '+';
		else if (prnt_check_flag(arg, FLAG_SPACE))
			arg->print_sign = ' ';
		u = d;
	}
	else
	{
		arg->print_sign = '-';
		u = -d;
	}
	arg->base = 10;
	return (u);
}

static unsigned long long	process_hex(t_arg_info *arg)
{
	unsigned long long	u;

	u = va_arg(arg->ap, unsigned);
	if (prnt_check_flag(arg, FLAG_SHARP) && u != 0)
		arg->prefix = arg->type == 'x' ? "0x" : "0X";
	else
		arg->prefix = "";
	arg->base = 16;
	arg->is_upcase = arg->type == 'x' ? 0 : 1;
	return (u);
}

static unsigned long long	process_octal(t_arg_info *arg)
{
	unsigned long long u;

	u = va_arg(arg->ap, unsigned);
	if (prnt_check_flag(arg, FLAG_SHARP))
		arg->prefix = "0";
	arg->base = 8;
	return (u);
}

void						prnt_process_numbers(t_arg_info *arg)
{
	unsigned long long u;

	u = 0;
	arg->is_upcase = 0;
	arg->prefix = NULL;
	arg->print_sign = 0;
	if (arg->type == 'p')
	{
		u = (unsigned long long)va_arg(arg->ap, void*);
		arg->prefix = "0x";
		arg->base = 16;
	}
	else if (arg->type == 'd' || arg->type == 'i')
		u = process_decimal(arg);
	else if (arg->type == 'o')
		u = process_octal(arg);
	else if (arg->type == 'u')
	{
		u = va_arg(arg->ap, unsigned);
		arg->base = 10;
	}
	else if (arg->type == 'x' || arg->type == 'X')
		u = process_hex(arg);
	prnt_nbr(arg, u);
}
