/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:48:39 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 17:14:30 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*src1;
	char			*dest1;

	i = 0;
	src1 = (char *) src;
	dest1 = (char *) dest;
	if (!dest && !src)
		return (NULL);
	while (n > i)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}
