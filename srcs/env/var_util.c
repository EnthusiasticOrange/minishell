/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:48:39 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 16:27:12 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmp_var_name(t_var *v, char *name)
{
	size_t len;

	len = ft_strlen(name);
	if (ft_strncmp(v->name, name, len) == 0 && ft_strlen(v->name) == len)
		return (0);
	else
		return (1);
}

char	*var_to_str(t_var *var)
{
	const char	*join[4];

	join[0] = var->name;
	join[1] = "=";
	join[2] = var->value;
	join[3] = NULL;
	return (ft_strjoin_array(join));
}

int		is_same_var(t_var *v1, t_var *v2)
{
	return (v1 == v2 ? 0 : 1);
}

void	update_underscore(char *path, char *last_arg)
{
	char	*tmp;
	char	**envp;

	if (!g_state.underscore)
		return ;
	if (!(tmp = ft_strjoin("_=", path)))
		return ;
	envp = g_state.envp;
	while (*envp)
	{
		if (ft_strncmp("_=", *envp, 2) == 0)
		{
			free(*envp);
			*envp = tmp;
			break ;
		}
		envp++;
	}
	if ((tmp = ft_strdup(last_arg)))
	{
		free(g_state.underscore->value);
		g_state.underscore->value = tmp;
	}
}
