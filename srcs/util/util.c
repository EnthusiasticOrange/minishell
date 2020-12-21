/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:28:24 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 19:55:29 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	char **tmp;

	tmp = arr;
	while (*tmp)
		free(*(tmp++));
	free(arr);
}

char	*skip_blanks(char *line)
{
	while (is_blank(*line))
		line++;
	return (line);
}

int		is_blank(int c)
{
	return (c == ' ' || c == '\t');
}

int		get_func_id(char *cmd)
{
	if (ft_strncmp("echo", cmd, 4) == 0 && ft_strlen(cmd) == 4)
		return (CMD_ECHO);
	else if (ft_strncmp("cd", cmd, 2) == 0 && ft_strlen(cmd) == 2)
		return (CMD_CD);
	else if (ft_strncmp("pwd", cmd, 3) == 0 && ft_strlen(cmd) == 3)
		return (CMD_PWD);
	else if (ft_strncmp("export", cmd, 6) == 0 && ft_strlen(cmd) == 6)
		return (CMD_EXPORT);
	else if (ft_strncmp("unset", cmd, 5) == 0 && ft_strlen(cmd) == 5)
		return (CMD_USNET);
	else if (ft_strncmp("env", cmd, 3) == 0 && ft_strlen(cmd) == 3)
		return (CMD_ENV);
	else if (ft_strncmp("exit", cmd, 4) == 0 && ft_strlen(cmd) == 4)
		return (CMD_EXIT);
	else
		return (CMD_EXEC);
}

void	print_prompt(void)
{
	char	*cwd;

	cwd = NULL;
	ft_putstr_fd(g_state.prompt, 1);
	if ((cwd = getcwd(cwd, 0)))
	{
		ft_printf_fd(1, ":%s", cwd);
		free(cwd);
	}
	ft_putstr_fd("> ", 1);
}
