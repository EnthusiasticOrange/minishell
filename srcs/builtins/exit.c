/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:25:17 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/21 18:32:49 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
}

void		builtin_exit(int argc, char **argv)
{
	char	*tmp;

	if (!g_state.is_child)
		ft_putendl_fd("exit", 2);
	if (argc == 1)
		exit(g_state.retcode);
	else
	{
		tmp = skip_spaces(argv[1]);
		if (*tmp == '+' || *tmp == '-')
			tmp++;
		while (ft_isdigit(*tmp))
			tmp++;
		tmp = skip_blanks(tmp);
		if (*tmp)
		{
			ft_printf_fd(2, "minishell: exit: %s: "
							"numeric argument required\n", argv[1]);
			exit(255);
		}
		if (argc == 2)
			exit(ft_atoi(argv[1]));
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_state.retcode = 1;
	}
}
