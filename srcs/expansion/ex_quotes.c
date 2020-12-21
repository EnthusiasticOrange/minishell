/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:57:45 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 20:09:45 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_dq_esc(int c)
{
	return (c == '\\' || c == '$' || c == '"');
}

static int		is_escaped(char cur, char next, char quote)
{
	if (cur != '\\')
		return (0);
	if (!quote || (quote == '"' && is_dq_esc(next)))
		return (1);
	else
		return (0);
}

static size_t	get_new_lengt(const char *s)
{
	size_t	new_len;
	char	quote;
	int		is_esc;

	new_len = 0;
	quote = 0;
	is_esc = 0;
	while (*s)
	{
		if ((is_esc = is_escaped(*s, *(s + 1), quote)))
			s++;
		if (!quote_check(*s, &quote, is_esc))
			new_len++;
		s++;
		is_esc = 0;
	}
	return (new_len);
}

char			*quote_expansion(const char *s)
{
	size_t	new_len;
	char	quote;
	char	*new_str;
	int		is_esc;

	new_len = get_new_lengt(s);
	if (!(new_str = malloc(new_len + 1)))
		return (NULL);
	new_str[new_len] = '\0';
	new_len = 0;
	quote = 0;
	is_esc = 0;
	while (*s)
	{
		if ((is_esc = is_escaped(*s, *(s + 1), quote)))
			s++;
		if (!quote_check(*s, &quote, is_esc))
			new_str[new_len++] = *s;
		s++;
		is_esc = 0;
	}
	return (new_str);
}
