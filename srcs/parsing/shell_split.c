/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:28:36 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 20:11:22 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		word_count(const char *str, int (*f)(int))
{
	size_t	count;
	int		is_word;
	char	quote;
	int		is_esc;

	count = 0;
	is_word = 0;
	quote = 0;
	is_esc = 0;
	while (*str)
	{
		if ((is_esc = (quote != '\'' && *str == '\\')))
			str++;
		if (f(*str) && !quote && !is_esc)
			is_word = 0;
		else if (is_word == 0)
		{
			count++;
			is_word = 1;
		}
		quote_check(*str, &quote, is_esc);
		is_esc = 0;
		str++;
	}
	return (count);
}

static int		word_size(char *str, int (*f)(int))
{
	size_t	i;
	char	quote;
	int		is_esc;

	i = 0;
	quote = 0;
	is_esc = 0;
	while (str[i])
	{
		if (quote != '\'' && str[i] == '\\')
		{
			is_esc = 1;
			i++;
		}
		if (f(str[i]) && !quote && !is_esc)
			break ;
		else
			quote_check(str[i], &quote, is_esc);
		i++;
		is_esc = 0;
	}
	return (i);
}

static char		*process_word(char **s, int (*f)(int))
{
	int		size;
	char	*str;

	while (f(**s))
		(*s)++;
	size = word_size(*s, f);
	str = ft_substr(*s, 0, size);
	*s += size;
	return (str);
}

char			**shell_split(char const *s, int (*f)(int), int *count)
{
	char	**ret;
	char	*str;
	int		i;

	str = (char*)s;
	*count = word_count(str, f);
	if (!(ret = ft_calloc(*count + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < *count)
	{
		ret[i] = process_word(&str, f);
		if (!ret[i])
		{
			free_array(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}
