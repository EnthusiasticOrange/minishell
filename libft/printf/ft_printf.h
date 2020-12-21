/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 23:41:59 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/14 19:21:24 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"

# include <stdarg.h>

# define FLAG_SHARP      (1)
# define FLAG_ZERO       (2)
# define FLAG_DASH       (4)
# define FLAG_SPACE      (8)
# define FLAG_PLUS       (16)

# define SIZE 40

typedef	struct	s_arg_info
{
	unsigned char	flags;
	int				width;
	int				precision;
	char			type;
	char			print_sign;
	char			*prefix;
	int				is_upcase;
	int				base;
	int				result;
	va_list			ap;
	int				fd;
}				t_arg_info;

int				prnt_process_arg(t_arg_info *arg, const char **fmt);
int				prnt_check_flag(t_arg_info *arg, unsigned char check);
void			prnt_process_string(t_arg_info *arg);
void			prnt_process_char(t_arg_info *arg);
void			prnt_process_numbers(t_arg_info *arg);
void			prnt_nbr(t_arg_info *arg, unsigned long long num);

#endif
