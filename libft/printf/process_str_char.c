/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_str_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:02:19 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/14 19:22:04 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	process_null(t_arg_info *arg, char **s)
{
	if (arg->precision != -1 && arg->precision < 6)
		*s = "";
	else
		*s = "(null)";
}

static void	print_padding(t_arg_info *arg, int len)
{
	while (arg->width-- > len)
		arg->result += write(arg->fd, " ", 1);
}

void		prnt_process_string(t_arg_info *arg)
{
	char	*s;
	int		d;
	int		i;

	s = va_arg(arg->ap, char*);
	if (s == NULL)
		process_null(arg, &s);
	d = ft_strlen(s);
	if (arg->precision < 0)
		arg->precision = 0x7fffffff;
	else if (arg->precision >= 0 && d > arg->precision)
		d = arg->precision;
	if (!prnt_check_flag(arg, FLAG_DASH))
		print_padding(arg, d);
	i = d;
	while (*s && i-- > 0)
		arg->result += write(arg->fd, s++, 1);
	if (prnt_check_flag(arg, FLAG_DASH))
		print_padding(arg, d);
}

void		prnt_process_char(t_arg_info *arg)
{
	char	c;

	c = va_arg(arg->ap, int);
	if (!prnt_check_flag(arg, FLAG_DASH))
		print_padding(arg, 1);
	arg->result += write(arg->fd, &c, 1);
	if (prnt_check_flag(arg, FLAG_DASH))
		print_padding(arg, 1);
}
