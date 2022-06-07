/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 19:03:49 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/14 19:22:46 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_padding(t_arg_info *arg, char padding)
{
	if (arg->print_sign)
		arg->width--;
	if (arg->prefix)
		arg->width -= ft_strlen(arg->prefix);
	while (arg->width-- > 0)
		arg->result += write(arg->fd, &padding, 1);
}

static void	print_number(t_arg_info *arg, char buf[SIZE], int digits)
{
	arg->width -= digits > arg->precision ? digits : arg->precision;
	if (!prnt_check_flag(arg, FLAG_DASH) && (!prnt_check_flag(arg, FLAG_ZERO)
		|| arg->precision != -1))
		print_padding(arg, ' ');
	if (arg->print_sign)
		arg->result += write(arg->fd, &arg->print_sign, 1);
	if (arg->prefix)
		arg->result += write(arg->fd, arg->prefix, ft_strlen(arg->prefix));
	if (!prnt_check_flag(arg, FLAG_DASH) && prnt_check_flag(arg, FLAG_ZERO)
		&& arg->precision == -1)
		print_padding(arg, '0');
	while (arg->precision-- > digits)
		arg->result += write(arg->fd, "0", 1);
	arg->result += write(arg->fd, buf + SIZE - digits, digits);
	if (prnt_check_flag(arg, FLAG_DASH))
		print_padding(arg, ' ');
}

void		prnt_nbr(t_arg_info *arg, unsigned long long num)
{
	static char			dig[] = "0123456789abcdef0123456789ABCDEF";
	char				buf[SIZE];
	int					digits;
	unsigned long long	n;

	digits = 0;
	n = num;
	while (1)
	{
		buf[SIZE - 1 - digits] = dig[(num % arg->base) + 16 * arg->is_upcase];
		num /= arg->base;
		digits++;
		if (num == 0)
			break ;
	}
	if (arg->precision == 0 && n == 0 && arg->type != 'p')
		digits = 0;
	print_number(arg, buf, digits);
}
