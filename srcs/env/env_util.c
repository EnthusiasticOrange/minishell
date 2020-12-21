/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:48:37 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 16:27:12 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_env_value(const char *name)
{
	t_list	*lst;
	t_var	*var;
	size_t	len;

	if (ft_strcmp("_", name) == 0 && g_state.underscore)
		return (g_state.underscore->value);
	lst = g_state.env_lst;
	while (lst)
	{
		var = lst->content;
		len = ft_strlen(var->name);
		if (len == ft_strlen(name) && ft_strncmp(var->name, name, len) == 0)
			return (var->value);
		lst = lst->next;
	}
	return (NULL);
}

char		**update_env(void)
{
	char		**new_env;
	size_t		size;
	t_list		*lst;

	size = ft_lstsize(g_state.env_lst) + (g_state.underscore ? 1 : 0);
	if (!(new_env = ft_calloc(size + 1, sizeof(char *))))
		return (NULL);
	lst = g_state.env_lst;
	size = 0;
	while (lst)
	{
		if (!(new_env[size++] = var_to_str(lst->content)))
		{
			free_array(new_env);
			return (NULL);
		}
		lst = lst->next;
	}
	if (g_state.underscore && !(new_env[size] = var_to_str(g_state.underscore)))
	{
		free_array(new_env);
		return (NULL);
	}
	return (new_env);
}

void		print_env(void *content)
{
	t_var *var;

	var = content;
	ft_printf_fd(1, "%s=%s\n", var->name, var->value);
}

void		update_env_value(t_var *v, char *value)
{
	free(v->value);
	if (!(v->value = ft_strdup(value)))
	{
		ft_lstremove_if(&g_state.env_lst, v, is_same_var);
		free_var(&v);
	}
}
