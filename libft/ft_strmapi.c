/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:23:35 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/30 10:45:52 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (!s || !f)
		return (NULL);
	i = 0;
	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char	ft_touppper(int unsigned i,char c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}
#include<stdio.h>
int main()
{
	char str[] = "abcde";
	char *result = ft_strmapi(str, &ft_touppper);
	printf("Original string: %s\n", str);
	printf("Modified string: %s\n", result);
	return 0;

}*/
