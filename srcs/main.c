/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 14:34:45 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/21 18:32:45 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd_sep(int c)
{
	return (c == ';');
}

static void	process_cmds(char **cmds)
{
	char	*cmd;

	while (*cmds)
	{
		cmd = *cmds;
		cmd = skip_blanks(cmd);
		run_command_line(cmd);
		if (dup2(g_state.stdin, STDIN_FILENO) == -1)
			ft_printf_fd(2, "minishell: Failed to revert STDIN: "
							"%s", strerror(errno));
		if (dup2(g_state.stdout, STDOUT_FILENO) == -1)
			ft_printf_fd(2, "minishell: Failed to revert STDOUT: "
							"%s", strerror(errno));
		cmds++;
	}
}

static void	process_line(char *line)
{
	char	**cmds;
	int		count;

	if (!(line = truncate_line(line)))
		return ;
	if ((cmds = shell_split(line, is_cmd_sep, &count)))
	{
		process_cmds(cmds);
		free_array(cmds);
	}
	else
		ft_putendl_fd("minishell: Failed to split commands", 2);
	free(line);
}

static void	read_commads(void)
{
	char	*line;
	int		result;

	print_prompt();
	while ((result = get_next_line(STDIN_FILENO, &line)) != -1)
	{
		if (result == 0)
			builtin_exit(1, NULL);
		if (check_line(line))
			process_line(line);
		free(line);
		print_prompt();
	}
	if (result == -1)
		builtin_exit(1, NULL);
}

int			main(int argc, char **argv, char **envp)
{
	UNUSED(argc);
	UNUSED(argv);
	g_state.prompt = "minishell";
	g_state.stdin = dup(STDIN_FILENO);
	g_state.stdout = dup(STDOUT_FILENO);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	if (!init_env(envp))
	{
		ft_putendl_fd("minishell: Failed to init environment variables", 2);
		return (1);
	}
	read_commads();
	return (g_state.retcode);
}
