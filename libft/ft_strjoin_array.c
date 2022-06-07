/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 17:31:07 by mjuli             #+#    #+#             */
/*   Updated: 2020/05/14 17:34:28 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	join_array(const char **array, char *res_str)
{
	size_t	len;
	size_t	shift;
	int		i;

	i = 0;
	len = 0;
	shift = 0;
	while (array[i])
	{
		len = ft_strlen(array[i]);
		ft_memcpy(res_str + shift, array[i], len);
		shift += len;
		i++;
	}
}

char		*ft_strjoin_array(const char **array)
{
	size_t	len;
	int		i;
	char	*res_str;

	i = 0;
	len = 0;
	while (array[i])
	{
		len += ft_strlen(array[i]);
		i++;
	}
	res_str = malloc(len + 1);
	if (res_str)
	{
		join_array(array, res_str);
		res_str[len] = '\0';
	}
	return (res_str);
}
