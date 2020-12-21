/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:23:19 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 16:27:12 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int argc, char **argv)
{
	char	*cwd;

	cwd = NULL;
	if (argc > 1 && *argv[1] == '-' && ft_strlen(argv[1]) > 1)
	{
		ft_putendl_fd("minishell: pwd: options are not supported", 2);
		g_state.retcode = 2;
	}
	else if ((cwd = getcwd(cwd, 0)))
	{
		ft_putendl_fd(cwd, 1);
		free(cwd);
		g_state.retcode = 0;
	}
	else
		g_state.retcode = 1;
}
