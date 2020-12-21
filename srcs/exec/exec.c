/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:53:06 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 14:30:48 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path(void)
{
	char	*value;

	value = get_env_value("PATH");
	if (value)
		return (ft_split(value, ':'));
	return (NULL);
}

static char	*get_full_path(char *name, char **path)
{
	size_t		i;
	char		*ret;
	const char	*join[4];
	struct stat	sb;

	ret = NULL;
	i = 0;
	while (path[i])
	{
		join[0] = path[i];
		join[1] = "/";
		join[2] = name;
		join[3] = NULL;
		ret = ft_strjoin_array(join);
		if (!ret || (stat(ret, &sb) == 0))
			break ;
		i++;
		free(ret);
		ret = NULL;
	}
	free_array(path);
	return (ret);
}

static void	swap(char **first, char **second)
{
	char *tmp;

	tmp = *first;
	*first = *second;
	*second = tmp;
}

static int	is_dir(char *name)
{
	struct stat	sb;

	return (stat(name, &sb) == 0 && S_ISDIR(sb.st_mode));
}

void		exec(int argc, char **argv)
{
	char		*cmd;
	char		**path;

	UNUSED(argc);
	cmd = argv[0];
	path = get_path();
	if (path && !ft_strchr(argv[0], '/'))
	{
		if (!*argv[0] || !(cmd = get_full_path(argv[0], path)))
		{
			ft_printf_fd(2, "minishell: %s: command not found\n", argv[0]);
			exit(127);
		}
		swap(&argv[0], &cmd);
	}
	else if (is_dir(argv[0]))
	{
		ft_printf_fd(2, "minishell: %s: is a directory\n", argv[0]);
		exit(126);
	}
	if (execve(argv[0], argv, g_state.envp) == -1)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", argv[0], strerror(errno));
		exit(errno == EACCES ? 126 : 127);
	}
}
