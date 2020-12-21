/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:24:56 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 17:00:36 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(int argc, char **argv)
{
	t_list	*item;
	t_var	*v;

	UNUSED(argc);
	while (*(++argv))
	{
		if (check_variable(*argv, '\0'))
		{
			item = ft_lstfind(g_state.env_lst, *argv, cmp_var_name);
			if (item)
			{
				v = item->content;
				ft_lstremove_if(&g_state.env_lst, v, is_same_var);
				free_var(&v);
			}
		}
		else
		{
			ft_printf_fd(2, "minishell: unset: `%s': "
							"not a valid identifier\n", *argv);
			g_state.retcode = 1;
		}
	}
}
