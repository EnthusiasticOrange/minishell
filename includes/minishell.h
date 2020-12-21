/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:12:25 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/21 00:18:11 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>

# define CMD_EXEC	0
# define CMD_ECHO	1
# define CMD_CD		2
# define CMD_PWD	3
# define CMD_EXPORT	4
# define CMD_USNET	5
# define CMD_ENV	6
# define CMD_EXIT	7

typedef struct	s_var
{
	char *name;
	char *value;
}				t_var;

typedef struct	s_state
{
	char	*prompt;
	char	**envp;
	t_list	*env_lst;
	t_var	*underscore;
	int		stdin;
	int		stdout;
	int		retcode;
	int		pid;
	int		is_child;
}				t_state;

t_state			g_state;

/*
** builtins
*/
void			cd(int argc, char **argv);
void			echo(int argc, char **argv);
void			env(int argc, char **argv);
void			builtin_exit(int argc, char **argv);
void			export(int argc, char **argv);
void			pwd(int argc, char **argv);
void			unset(int argc, char **argv);

/*
** env
*/
int				init_env(char **envp);
void			set_env(const char *line);
char			*get_env_value(const char *name);
char			**update_env(void);
void			print_env(void *content);
void			update_env_value(t_var *v, char *value);
int				cmp_var_name(t_var *v, char *name);
char			*var_to_str(t_var *var);
int				is_same_var(t_var *v1, t_var *v2);
void			update_underscore(char *path, char *last_arg);
t_var			*create_var_from_str(const char *line);
t_var			*create_var(char *name, char *value);
int				check_variable(char *line, char c);
void			free_var(t_var **var);

/*
** exec
*/
int				is_pipe(int c);
int				move_fd(int fd1, int fd2);
void			run_command_line(char *cmd);
void			exec(int argc, char **argv);

/*
** expansion
*/
char			*quote_expansion(const char *line);
char			*variable_expansion(const char *line);
char			*escape_string(char *str);
char			*get_var_name(const char *line);
char			*get_var_value(const char *var_name);

/*
** parsing
*/
char			**create_arguments(int in, int out, char *line, int *argc);
int				check_line(char *s);
char			**shell_split(char const *s, int (*f)(int), int *count);
char			*shell_strchr(const char *s, int (*f)(int));

/*
** redir
*/
char			*remove_redir(char *cmd);
int				is_control(int c);
int				is_control_or_space(int c);
int				is_in_redir(int c);
int				is_out_redir(int c);
int				is_redir(int c);
char			*process_redir(int in, int out, char *cmd);

/*
** signals
*/
void			sigint_handler(int signum);
void			sigquit_handler(int signum);

/*
** util
*/
int				quote_check(char c, char *quote, int is_esc);
char			*truncate_line(char *line);
void			free_array(char **arr);
char			*skip_blanks(char *line);
int				is_blank(int c);
int				get_func_id(char *cmd);
void			print_prompt();

#endif
