/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:24:45 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 21:17:14 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	cal_len(char const *s1, char const *set, int *start)
{
	int	slen;
	int	count;
	int	i;

	i = 0;
	count = 0;
	slen = ft_strlen(s1);
	while (s1[i])
	{
		if (!ft_check(s1[i], set))
			break ;
		count++;
		i++;
	}
	*start = count;
	while (slen - 1 != i - 1)
	{
		if (!ft_check(s1[slen - 1], set))
			break ;
		count++;
		slen--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		size;
	int		i;
	int		x;

	x = 0;
	i = 0;
	if (!s1 || !set)
		return (0);
	size = ft_strlen(s1) - cal_len(s1, set, &x);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	while (i < size)
	{
		ptr[i] = s1[x];
		i++;
		x++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int main() {
    const char *str = "   Hello, World!   ";
    const char *set = " ";
    char *result = ft_strtrim(str, set);
    printf("str: \"%s\"\n", str);
    printf("Trimmed: \"%s\"\n", result);
}*/
