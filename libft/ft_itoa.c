/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:46:38 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 18:08:04 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_len(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	ln;

	ln = (long) n;
	size = cal_len(ln);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	if (ln < 0)
	{
		ln *= -1;
		ptr[0] = '-';
	}
	ptr[size--] = '\0';
	if (ln == 0)
		ptr[0] = '0';
	while (ln > 0)
	{
		ptr[size--] = (ln % 10) + 48;
		ln /= 10;
	}
	return (ptr);
}
