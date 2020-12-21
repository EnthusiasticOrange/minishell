/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:54:24 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 15:57:27 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_pipe(int c)
{
	return (c == '|');
}

int		move_fd(int fd1, int fd2)
{
	if (fd1 != fd2)
	{
		if (dup2(fd1, fd2) == -1)
		{
			ft_printf_fd(2, "minishell: Failed to move fd: "
							"%s\n", strerror(errno));
			return (0);
		}
		close(fd1);
	}
	return (1);
}
