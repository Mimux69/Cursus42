/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:25:13 by acronert          #+#    #+#             */
/*   Updated: 2023/11/08 14:07:08 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t size)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	if (!size)
		return (0);
	if (big == little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < size)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j < size - 1))
		{
			j++;
		}
		if (!little[j])
			return (&((char *)big)[i]);
		i++;
	}
	return (0);
}
