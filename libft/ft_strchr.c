/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:42:59 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 19:13:06 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)str;
	while (ptr[i])
	{
		if (ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	if (ptr[i] == (unsigned char)c)
		return (&ptr[i]);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	printf("%s\n",ft_strchr("test strchr", 's' ));
 	printf("%s\n",strchr("test strchr", 's'));
 	return 0;
}
*/
