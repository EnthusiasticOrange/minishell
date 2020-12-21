/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:34:27 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 18:35:46 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote_removal(char **argv)
{
	char *tmp;

	while (*argv)
	{
		if (!(tmp = quote_expansion(*argv)))
		{
			ft_putendl_fd("minishell: Failed to remove quotes", 2);
			return ;
		}
		free(*argv);
		*argv = tmp;
		argv++;
	}
}

char		**create_arguments(int in, int out, char *line, int *argc)
{
	char	**argv;
	char	*tmp;

	if (!(line = process_redir(in, out, line)))
	{
		g_state.retcode = 1;
		return (NULL);
	}
	tmp = variable_expansion(line);
	free(line);
	if (!tmp)
	{
		ft_putendl_fd("minishell: Failed to expand variables", 2);
		return (NULL);
	}
	if (!(argv = shell_split(tmp, is_blank, argc)))
	{
		ft_putendl_fd("minishell: Failed to split arguments", 2);
		free(line);
		return (NULL);
	}
	quote_removal(argv);
	free(tmp);
	return (argv);
}
