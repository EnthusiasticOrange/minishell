/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:52:53 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/21 20:28:55 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void(*g_cmd_arr[8])(int, char**) =
{
	exec,
	echo,
	cd,
	pwd,
	export,
	unset,
	env,
	builtin_exit
};

static void	run_fork(int in, int pipe_arr[2], int argc, char **argv)
{
	int	out;

	out = pipe_arr[1];
	update_underscore(argv[0], argv[argc - 1]);
	g_state.pid = fork();
	if (g_state.pid == -1)
		ft_printf_fd(2, "minishell: Fork error: %s\n", strerror(errno));
	else if (g_state.pid == 0)
	{
		close(pipe_arr[0]);
		g_state.is_child = 1;
		if (!move_fd(in, STDIN_FILENO))
			exit(-1);
		if (!move_fd(out, STDOUT_FILENO))
			exit(-1);
		g_cmd_arr[get_func_id(argv[0])](argc, argv);
		exit(g_state.retcode);
	}
	if (pipe_arr[1] != STDOUT_FILENO)
		close(pipe_arr[1]);
	close(in);
}

static int	pipe_commands(char **pipe_cmds, int count)
{
	int		pipe_arr[2];
	int		in;
	int		i;
	int		argc;
	char	**argv;

	in = STDIN_FILENO;
	i = 0;
	while (i < count - 1)
	{
		pipe(pipe_arr);
		if ((argv = create_arguments(in, pipe_arr[1], pipe_cmds[i], &argc)))
		{
			run_fork(in, pipe_arr, argc, argv);
			in = pipe_arr[0];
			free_array(argv);
		}
		i++;
	}
	return (in);
}

static int	run_builtin(int argc, char **argv)
{
	int		func_id;

	if (argc == 0)
		return (1);
	func_id = get_func_id(argv[0]);
	if (func_id != CMD_EXEC)
	{
		update_underscore(argv[0], argv[argc - 1]);
		g_cmd_arr[func_id](argc, argv);
	}
	return (func_id);
}

static void	run_last(int in, int count, char *cmd)
{
	int		argc;
	char	**argv;
	int		pipe_arr[2];

	pipe_arr[0] = -1;
	pipe_arr[1] = STDOUT_FILENO;
	if ((argv = create_arguments(in, STDOUT_FILENO, cmd, &argc)))
	{
		if (count == 1)
		{
			if (!run_builtin(argc, argv))
				run_fork(in, pipe_arr, argc, argv);
		}
		else
			run_fork(in, pipe_arr, argc, argv);
		free_array(argv);
	}
}

void		run_command_line(char *cmd)
{
	char	**pipe_cmds;
	int		count;
	int		in;

	g_state.pid = 0;
	pipe_cmds = shell_split(cmd, is_pipe, &count);
	in = pipe_commands(pipe_cmds, count);
	run_last(in, count, pipe_cmds[count - 1]);
	if (g_state.pid > 0)
	{
		waitpid(g_state.pid, &g_state.retcode, 0);
		g_state.retcode = WEXITSTATUS(g_state.retcode);
	}
	close(in);
	errno = 0;
	while (errno != ECHILD)
		wait(NULL);
	g_state.pid = 0;
	free_array(pipe_cmds);
}
