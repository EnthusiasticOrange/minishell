/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_rem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:09:05 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 19:55:28 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_redir(char *cmd)
{
	char *start;
	char *end;
	char *tmp;
	char *cmd_new;

	start = cmd;
	cmd_new = ft_strdup(cmd);
	while ((tmp = shell_strchr(start, is_redir)))
	{
		end = tmp;
		end += (ft_strncmp(end, ">>", 2) == 0 ? 2 : 1);
		end = skip_blanks(end);
		end = shell_strchr(end, is_control_or_space);
		if (!end)
			end = "";
		tmp = ft_substr(start, 0, tmp - start);
		if (cmd_new)
			free(cmd_new);
		cmd_new = ft_strjoin(tmp, end);
		free(tmp);
		start = cmd_new;
	}
	return (cmd_new);
}
