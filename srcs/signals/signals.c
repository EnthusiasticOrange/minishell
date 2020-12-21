/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:10:31 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 16:27:12 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum)
{
	UNUSED(signum);
	if (g_state.pid)
	{
		ft_putchar_fd('\n', 1);
		kill(g_state.pid, SIGINT);
		g_state.retcode = 130;
	}
	else
	{
		ft_putstr_fd("\b\b  \b\b\n", 1);
		print_prompt();
	}
}

void	sigquit_handler(int signum)
{
	UNUSED(signum);
	if (g_state.pid)
	{
		ft_putendl_fd("Quit: 3", 1);
		kill(g_state.pid, SIGQUIT);
		g_state.retcode = 131;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 1);
}
