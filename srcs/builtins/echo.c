/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:22:32 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 16:27:12 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(int argc, char **argv)
{
	int	is_newline;

	is_newline = 1;
	if (argc > 1)
	{
		argv++;
		while (*argv && ft_strncmp("-n", *argv, 2) == 0)
		{
			is_newline = 0;
			argv++;
		}
		while (*argv)
		{
			ft_putstr_fd(*argv, 1);
			argv++;
			if (*argv)
				ft_putchar_fd(' ', 1);
		}
	}
	if (is_newline)
		ft_putchar_fd('\n', 1);
	g_state.retcode = 0;
}
