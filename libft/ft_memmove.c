/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:47:46 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 18:50:01 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*sptr;
	char	*dptr;

	if (!dest && !src)
		return (NULL);
	sptr = (char *)src;
	dptr = (char *)dest;
	if (dest <= src)
		ft_memcpy(dptr, sptr, n);
	else
	{
		while (n > 0)
		{
			dptr[n - 1] = sptr[n - 1];
			n--;
		}
	}
	return (dptr);
}
