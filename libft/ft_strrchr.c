/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:10:32 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/18 11:33:37 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*ptr;
	int				len;
	unsigned char	x;

	x = (unsigned char)c;
	ptr = (char *)str;
	len = ft_strlen(ptr);
	if (*(ptr + len) == x)
		return (ptr + len);
	len--;
	while (len >= 0)
	{
		if (*(ptr + len) == x)
			return (ptr + len);
		len--;
	}
	return (NULL);
}
