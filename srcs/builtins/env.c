/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:24:26 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/20 16:08:14 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(int argc, char **argv)
{
	UNUSED(argv);
	if (argc > 1)
	{
		ft_putendl_fd("minishell: env: "
						"options and argumetns are not supported", 2);
		g_state.retcode = 2;
		return ;
	}
	ft_lstiter(g_state.env_lst, print_env);
	if (g_state.underscore)
		print_env(g_state.underscore);
}
