/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 00:05:52 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/21 00:42:28 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*truncate_line(char *line)
{
	size_t	start;
	size_t	end;

	start = ft_strspn(line, " \t");
	end = ft_strlen(line);
	while (end > 0)
	{
		if (line[end - 1] != ' ' && line[end - 1] != '\t')
			break ;
		end--;
	}
	if (line[end - 1] == '\\')
		end++;
	if (end >= start)
		return (ft_substr(line, start, end - start));
	else
		return (NULL);
}
