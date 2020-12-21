/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:21:33 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 18:16:03 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_new_pwd(t_var *pwd)
{
	char *cwd;

	cwd = NULL;
	if ((cwd = getcwd(cwd, 0)))
	{
		if (!pwd)
		{
			pwd = create_var("PWD", cwd);
			ft_lstpush_back(&g_state.env_lst, pwd);
		}
		else
			update_env_value(pwd, cwd);
		free(cwd);
	}
}

static void	remove_oldpwd(void)
{
	t_list	*item;
	t_var	*v;

	item = ft_lstfind(g_state.env_lst, "OLDPWD", cmp_var_name);
	if (item)
	{
		v = item->content;
		ft_lstremove_if(&g_state.env_lst, v, is_same_var);
		free_var(&v);
	}
}

static void	update_pwd_variables(void)
{
	t_list	*tmp;
	t_var	*old_pwd;
	t_var	*pwd;

	tmp = ft_lstfind(g_state.env_lst, "PWD", cmp_var_name);
	pwd = (tmp != NULL ? tmp->content : NULL);
	tmp = ft_lstfind(g_state.env_lst, "OLDPWD", cmp_var_name);
	old_pwd = (tmp != NULL ? tmp->content : NULL);
	if (pwd)
	{
		if (!old_pwd)
		{
			old_pwd = create_var("OLDPWD", pwd->value);
			if (old_pwd)
				ft_lstpush_back(&g_state.env_lst, old_pwd);
		}
		else
			update_env_value(old_pwd, pwd->value);
	}
	else if (tmp)
		remove_oldpwd();
	set_new_pwd(pwd);
}

void		cd(int argc, char **argv)
{
	char	*line;

	g_state.retcode = 0;
	if (argc == 1)
	{
		if (!(line = get_env_value("HOME")))
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			g_state.retcode = 1;
			return ;
		}
	}
	else
		line = argv[1];
	if (ft_strlen(line) && (g_state.retcode = chdir(line)) == -1)
		ft_printf_fd(2, "minishell: cd: %s: %s\n", line, strerror(errno));
	else
		update_pwd_variables();
	g_state.retcode = (g_state.retcode == -1 ? 1 : 0);
}
