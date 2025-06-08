/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:44:00 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 20:45:18 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	slen;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		len = 0;
	else if (len + start > slen)
		len = slen - start;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = s[i + start];
		i++;
	}
	res[len] = '\0';
	return (res);
}
/*
int main() {
    const char *s = "Hello World!";
    char *result = ft_substr(s, 6, 10);
    printf("string:%s\n", result);

    return 0;
}*/
