/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:25:51 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/21 01:17:04 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*dummy_copy(void *content)
{
	return (content);
}

static void	dummy_del(void *content)
{
	UNUSED(content);
}

static int	sort_value(t_var *v1, t_var *v2)
{
	return (ft_strcmp(v1->name, v2->name));
}

static void	print_export(void *content)
{
	t_var	*v;
	char	*val;

	v = content;
	val = v->value;
	ft_printf_fd(1, "declare -x %s=\"", v->name);
	while (*val)
	{
		if (*val == '\\' || *val == '$' || *val == '"')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(*(val++), 1);
	}
	ft_putendl_fd("\"", 1);
}

void		export(int argc, char **argv)
{
	t_list *sort;

	if (argc == 1)
	{
		sort = ft_lstmap(g_state.env_lst, dummy_copy, dummy_del);
		ft_lstsort(&sort, sort_value);
		ft_lstiter(sort, print_export);
		ft_lstclear(&sort, dummy_del);
	}
	else
	{
		while (*(++argv))
		{
			if (check_variable(*argv, '='))
				set_env(*argv);
			else
			{
				ft_printf_fd(2, "minishell: export: `%s': "
								"not a valid identifier\n", *argv);
				g_state.retcode = 1;
			}
		}
	}
}
