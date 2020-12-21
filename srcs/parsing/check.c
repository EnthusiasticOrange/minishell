/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:06:57 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/21 00:00:19 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_not_empty(char *line)
{
	line = skip_blanks(line);
	return (ft_strlen(line));
}

static int	check_quotes(char *line)
{
	char	quote;
	int		is_esc;

	quote = 0;
	is_esc = 0;
	while (*line)
	{
		if (quote != '\'' && *line == '\\')
		{
			is_esc = 1;
			line++;
		}
		quote_check(*line, &quote, is_esc);
		if (!*line)
			break ;
		line++;
		is_esc = 0;
	}
	if (is_esc)
		quote = '\\';
	return (quote);
}

static char	check_tokens(char *s)
{
	char	tok;
	char	qt;

	tok = ';';
	qt = 0;
	while (*(s = skip_blanks(s)))
	{
		if (!qt && (*s == '\'' || *s == '"'))
			qt = *s;
		else if (qt && *s == qt)
			qt = 0;
		if (!qt && (*s == '|' || *s == ';' || *s == '<' || *s == '>'))
		{
			if (*s == '>' && *(s + 1) == '>')
				s++;
			if ((tok == ';' && (*s == '|' || *s == ';')) || (tok && tok != ';'))
				return (*s);
			tok = *s;
		}
		else
			tok = 0;
		s++;
	}
	return (tok == ';' ? 0 : tok);
}

int			check_line(char *line)
{
	char c;

	if (!check_not_empty(line))
		return (0);
	else if ((c = check_quotes(line)))
	{
		ft_printf_fd(2, "minishell: unexpected EOF while looking for matching "
						"`%c'\n", c);
		g_state.retcode = 2;
		return (0);
	}
	else if ((c = check_tokens(line)))
	{
		ft_printf_fd(2, "minishell: syntax error near unexpected token "
						"`%c'\n", c);
		g_state.retcode = 258;
		return (0);
	}
	return (1);
}
