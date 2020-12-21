/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 23:51:49 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/14 19:21:14 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	process_format(t_arg_info *arg)
{
	if (arg->type == 's')
		prnt_process_string(arg);
	else if (arg->type == 'c')
		prnt_process_char(arg);
	else if (arg->type == '%')
		arg->result += write(arg->fd, "%", 1);
	else
		prnt_process_numbers(arg);
}

int			ft_printf_fd(int fd, const char *format, ...)
{
	t_arg_info		arg;

	arg.fd = fd;
	arg.result = 0;
	va_start(arg.ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (-1);
			if (!prnt_process_arg(&arg, &format))
				return (-1);
			process_format(&arg);
		}
		else
			arg.result += write(arg.fd, format, 1);
		format++;
	}
	va_end(arg.ap);
	return (arg.result);
}
