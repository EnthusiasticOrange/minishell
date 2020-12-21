/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 16:09:08 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 21:37:41 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_filename(char *line, size_t *len)
{
	char	*tmp;
	char	*filename;
	size_t	temp_len;

	filename = NULL;
	line = skip_blanks(line);
	tmp = shell_strchr(line, is_control_or_space);
	if (tmp)
		temp_len = tmp - line;
	else
		temp_len = ft_strlen(line);
	*len = temp_len;
	tmp = ft_substr(line, 0, temp_len);
	if (tmp)
	{
		filename = quote_expansion(tmp);
		free(tmp);
	}
	return (filename);
}

static char		*redir_fd(int fd, char *name, int flags, int mode)
{
	int		newfd;
	char	*filename;
	size_t	len;

	filename = get_filename(name, &len);
	if (!filename)
	{
		ft_putendl_fd("minishell: Failed to get reditect filename", 2);
		return (NULL);
	}
	newfd = open(filename, flags, mode);
	if (newfd == -1)
		ft_printf_fd(2, "minishell: %s: %s\n", filename, strerror(errno));
	else if (newfd != -1 && dup2(newfd, fd) == -1)
	{
		close(newfd);
		newfd = -1;
	}
	free(filename);
	return (newfd == -1 ? NULL : name + len);
}

static char		*redir_in(int in, char *cmd)
{
	int		flags;
	int		mode;

	flags = O_RDONLY;
	mode = 0;
	cmd = skip_blanks(cmd);
	return (redir_fd(in, cmd, flags, mode));
}

static char		*redir_out(int out, char *cmd)
{
	int		flags;
	int		mode;

	flags = O_WRONLY | O_CREAT;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (*cmd == '>')
	{
		flags |= O_APPEND;
		cmd++;
	}
	else
		flags |= O_TRUNC;
	cmd = skip_blanks(cmd);
	return (redir_fd(out, cmd, flags, mode));
}

char			*process_redir(int in, int out, char *cmd)
{
	char	*tmp;

	tmp = cmd;
	while ((tmp = shell_strchr(tmp, is_redir)))
	{
		if (*tmp == '<')
			tmp = redir_in(in, tmp + 1);
		else
			tmp = redir_out(out, tmp + 1);
		if (!tmp)
			return (NULL);
	}
	return (remove_redir(cmd));
}
