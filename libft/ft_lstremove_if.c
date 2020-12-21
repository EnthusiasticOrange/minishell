/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 10:25:51 by mjuli             #+#    #+#             */
/*   Updated: 2020/03/11 20:35:30 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *current;
	t_list *prev;

	if (*begin_list == 0)
		return ;
	prev = *begin_list;
	current = prev->next;
	while (current)
	{
		if ((*cmp)(current->content, data_ref) == 0)
		{
			prev->next = current->next;
			free(current);
		}
		else
			prev = prev->next;
		current = prev->next;
	}
	if ((*cmp)((*begin_list)->content, data_ref) == 0)
	{
		current = *begin_list;
		*begin_list = (*begin_list)->next;
		free(current);
	}
}
