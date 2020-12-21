/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:03:19 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 23:37:53 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char c, char *quote, int is_esc)
{
	if (!*quote && !is_esc && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote && c == *quote && !is_esc)
		*quote = 0;
	else
		return (0);
	return (1);
}
