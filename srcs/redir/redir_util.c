/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:08:50 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 19:26:03 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_control(int c)
{
	return (c == '<' || c == '>' || c == '|' || c == ';');
}

int	is_control_or_space(int c)
{
	return (is_control(c) || is_blank(c));
}

int	is_in_redir(int c)
{
	return (c == '<');
}

int	is_out_redir(int c)
{
	return (c == '>');
}

int	is_redir(int c)
{
	return (is_in_redir(c) || is_out_redir(c));
}
