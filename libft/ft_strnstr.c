/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:35:00 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 20:26:51 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	n;

	if (*s2 == '\0')
		return ((char *) s1);
	n = ft_strlen(s2);
	while (*s1 != '\0' && len >= n)
	{
		if (*s1 == *s2 && ft_memcmp(s1, s2, n) == 0)
			return ((char *) s1);
		s1++;
		len--;
	}
	return (NULL);
}
/*
int main() {
    const char *s1 = "Hello, World!";
    const char *s2 = "or";
    size_t len = 13;

    char *result = ft_strnstr(s1, s2, len);

    printf("position: %ld\n", result - s1);
    printf("string: %s\n", result);

    return 0;
}*/
