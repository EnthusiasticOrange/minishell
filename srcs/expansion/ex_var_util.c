/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_var_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:39:38 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 23:48:45 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*escape_string(char *str)
{
	size_t	len;
	char	*new_str;

	len = 0;
	new_str = str;
	while (*str)
	{
		if (*(str++) == '\\')
			len++;
		len++;
	}
	str = new_str;
	if ((new_str = ft_calloc(1, len + 1)))
	{
		len = 0;
		while (*str)
		{
			if (*(str) == '\\')
				new_str[len++] = '\\';
			new_str[len++] = *(str++);
		}
	}
	return (new_str);
}

char	*get_var_name(const char *line)
{
	size_t len;

	if (*line == '?')
		return (ft_strdup("?"));
	len = 0;
	if (ft_isalpha(line[len]) || line[len] == '_')
	{
		while (ft_isalnum(line[len]) || line[len] == '_')
			len++;
	}
	return (ft_substr(line, 0, len));
}

char	*get_var_value(const char *var_name)
{
	char	*var_value;

	if (*var_name == '?')
		return (ft_itoa(g_state.retcode));
	if ((var_value = get_env_value(var_name)))
		var_value = escape_string(var_value);
	return (var_value);
}
