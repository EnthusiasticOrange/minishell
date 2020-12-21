/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:48:30 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 23:45:59 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pwd_var(void)
{
	t_var	*pwd;
	t_list	*item;
	char	*cwd;

	cwd = NULL;
	if ((cwd = getcwd(cwd, 0)))
	{
		if ((pwd = create_var("PWD", cwd)))
		{
			item = ft_lstfind(g_state.env_lst, "PWD", cmp_var_name);
			if (!item)
				ft_lstpush_back(&g_state.env_lst, pwd);
			else
			{
				update_env_value(item->content, cwd);
				free_var(&pwd);
			}
		}
		free(cwd);
	}
}

int			init_env(char **envp)
{
	t_list	*tmp;
	t_var	*var;

	while (*envp)
	{
		if (!(var = create_var_from_str(*envp)))
			return (0);
		if (*var->name == '_' && ft_strlen(var->name) == 1)
			g_state.underscore = var;
		else
		{
			if (!(tmp = ft_lstnew(var)))
			{
				free(var);
				return (0);
			}
			ft_lstadd_back(&g_state.env_lst, tmp);
		}
		envp++;
	}
	init_pwd_var();
	g_state.envp = update_env();
	return (g_state.envp ? 1 : 0);
}

static void	update_variable(t_var *v)
{
	t_list	*item;
	t_var	*tmp;

	if (ft_strncmp(v->name, "_", 1) == 0 && ft_strlen(v->name) == 1)
	{
		free_var(&g_state.underscore);
		g_state.underscore = v;
		return ;
	}
	if ((item = ft_lstfind(g_state.env_lst, v->name, cmp_var_name)))
	{
		tmp = item->content;
		update_env_value(tmp, v->value);
		free_var(&v);
	}
	else
		ft_lstpush_back(&g_state.env_lst, v);
}

void		set_env(const char *line)
{
	char	*eq;
	t_var	*var;
	char	**envp;

	eq = ft_strchr(line, '=');
	if (!eq)
		return ;
	if (!(var = create_var_from_str(line)))
	{
		ft_putendl_fd("minishell: Failed to update env", 2);
		return ;
	}
	update_variable(var);
	if (!(envp = update_env()))
		ft_putendl_fd("minishell: Failed to update envp", 2);
	else
	{
		free_array(g_state.envp);
		g_state.envp = envp;
	}
}
