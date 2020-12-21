/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:28:32 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 20:08:27 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_strchr(const char *s, int (*f)(int))
{
	char	quote;
	int		is_esc;

	quote = 0;
	is_esc = 0;
	while (*s)
	{
		if (quote != '\'' && *s == '\\')
		{
			is_esc = 1;
			s++;
		}
		if (f(*s) && !quote)
			return ((char*)s);
		else
			quote_check(*s, &quote, is_esc);
		s++;
		is_esc = 0;
	}
	return (NULL);
}
