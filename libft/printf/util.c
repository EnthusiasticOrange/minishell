/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 00:00:14 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/14 19:22:22 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				check_format(char c)
{
	return (c == 'p' || c == 'd' || c == 'i' || c == 'o' || c == 'u' ||
			c == 'x' || c == 'X' || c == 's' || c == 'c' || c == '%');
}

static unsigned char	process_flags(const char **fmt)
{
	unsigned char	flags;
	char			c;

	flags = 0;
	while (1)
	{
		c = **fmt;
		if (c == '#')
			flags |= FLAG_SHARP;
		else if (c == '0')
			flags |= FLAG_ZERO;
		else if (c == '-')
			flags |= FLAG_DASH;
		else if (c == ' ')
			flags |= FLAG_SPACE;
		else if (c == '+')
			flags |= FLAG_PLUS;
		else
			break ;
		(*fmt)++;
	}
	return (flags);
}

static int				process_width_prec(t_arg_info *arg, const char **fmt)
{
	int d;

	d = 0;
	if (ft_isdigit(**fmt))
	{
		while (ft_isdigit(**fmt))
		{
			d = 10 * d + **fmt - '0';
			(*fmt)++;
		}
	}
	else if (**fmt == '*')
	{
		d = va_arg(arg->ap, int);
		(*fmt)++;
	}
	return (d);
}

int						prnt_check_flag(t_arg_info *arg, unsigned char check)
{
	return (arg->flags & check);
}

int						prnt_process_arg(t_arg_info *arg, const char **fmt)
{
	arg->flags = process_flags(fmt);
	arg->width = process_width_prec(arg, fmt);
	if (arg->width < 0)
	{
		arg->flags |= FLAG_DASH;
		arg->width = -arg->width;
	}
	arg->precision = -1;
	if (**fmt == '.')
	{
		(*fmt)++;
		arg->precision = process_width_prec(arg, fmt);
		if (arg->precision < 0)
			arg->precision = -1;
	}
	if (check_format(**fmt))
	{
		arg->type = **fmt;
		return (1);
	}
	else
		return (0);
}
