/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:57:49 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 23:23:26 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	get_var_length(const char **s)
{
	char	*name;
	char	*value;
	size_t	len;

	len = 0;
	name = get_var_name(*s);
	if (name)
	{
		if (ft_strlen(name) == 0)
			len = 1;
		else if ((value = get_var_value(name)))
		{
			len = ft_strlen(value);
			free(value);
		}
		(*s) += ft_strlen(name);
		free(name);
	}
	return (len);
}

static size_t	get_new_length(const char *s)
{
	size_t	new_len;
	char	quote;
	int		is_esc;

	new_len = 0;
	quote = 0;
	is_esc = 0;
	while (*s)
	{
		if ((is_esc = (quote != '\'' && *s == '\\' && *(s + 1) == '$')))
			s++;
		quote_check(*s, &quote, is_esc);
		if (*(s++) == '$' && !is_esc && quote != '\'')
			new_len += get_var_length(&s);
		else
			new_len++;
		is_esc = 0;
	}
	return (new_len);
}

static char		*copy_var_value(const char **s, char *new_line)
{
	size_t	var_len;
	size_t	name_len;
	char	*name;
	char	*value;

	(*s)++;
	if ((name = get_var_name(*s)))
	{
		name_len = ft_strlen(name);
		if (name_len == 0)
			*(new_line++) = '$';
		else if ((value = get_var_value(name)))
		{
			var_len = ft_strlen(value);
			ft_memcpy(new_line, value, var_len);
			free(value);
			new_line += var_len;
		}
		*s += name_len;
		free(name);
	}
	return (new_line);
}

static void		copy_string(const char *s, char *new_line)
{
	char		quote;
	int			is_esc;

	quote = 0;
	is_esc = 0;
	while (*s)
	{
		if ((is_esc = (quote != '\'' && *s == '\\' && *(s + 1) == '$')))
			s++;
		quote_check(*s, &quote, is_esc);
		if (*s == '$' && !is_esc && quote != '\'')
			new_line = copy_var_value(&s, new_line);
		else
			*(new_line++) = *(s++);
		is_esc = 0;
	}
}

char			*variable_expansion(const char *line)
{
	size_t	new_len;
	char	*new_str;

	new_len = get_new_length(line);
	if (!(new_str = malloc(new_len + 1)))
		return (NULL);
	new_str[new_len] = '\0';
	copy_string(line, new_str);
	return (new_str);
}
