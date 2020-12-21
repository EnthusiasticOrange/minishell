/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 11:30:19 by mjuli             #+#    #+#             */
/*   Updated: 2020/03/11 21:18:35 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	data_swap(void **data1, void **data2)
{
	void *tmp;

	tmp = *data1;
	*data1 = *data2;
	*data2 = tmp;
}

void		ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*list;
	t_list	*end;
	int		swapped;

	end = 0;
	swapped = 1;
	if (*begin_list == 0)
		return ;
	while (swapped)
	{
		swapped = 0;
		list = *begin_list;
		while (list->next != end)
		{
			if ((*cmp)(list->content, list->next->content) > 0)
			{
				swapped = 1;
				data_swap(&list->content, &list->next->content);
			}
			list = list->next;
		}
		end = list;
	}
}
