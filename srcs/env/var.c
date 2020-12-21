/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:48:44 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 17:00:45 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*create_var_from_str(const char *line)
{
	t_var	*var;
	char	*sep;

	var = ft_calloc(1, sizeof(t_var));
	if (var)
	{
		sep = ft_strchr(line, '=');
		if (sep)
		{
			var->name = ft_substr(line, 0, sep - line);
			var->value = ft_substr(sep + 1, 0, __SIZE_MAX__);
		}
		if (!sep || !var->name || !var->value)
			free_var(&var);
	}
	return (var);
}

t_var	*create_var(char *name, char *value)
{
	t_var *var;

	var = ft_calloc(1, sizeof(t_var));
	if (var)
	{
		var->name = ft_strdup(name);
		var->value = ft_strdup(value);
		if (!var || !var->name || !var->value)
			free_var(&var);
	}
	return (var);
}

int		check_variable(char *line, char c)
{
	size_t i;

	i = 0;
	if (!ft_isalpha(line[i]) && line[i] != '_')
		return (0);
	while (line[i] && line[i] != c)
	{
		if (!ft_isalnum(line[i]) && line[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_var(t_var **var)
{
	if (*var)
	{
		if ((*var)->name)
			free((*var)->name);
		if ((*var)->value)
			free((*var)->value);
		free(*var);
		*var = NULL;
	}
}
