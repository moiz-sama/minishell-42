/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:52:15 by saderdou          #+#    #+#             */
/*   Updated: 2023/11/29 20:19:30 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char	*dest, const char	*src, size_t size)
{
	size_t	size_dest;
	size_t	i;
	size_t	size_src;

	i = 0;
	size_dest = 0;
	while (dest[size_dest] != '\0')
		size_dest++;
	size_src = 0;
	while (src[size_src])
		size_src++;
	if (size == 0)
		return (size_src);
	if (size <= size_dest)
		return (size_src + size);
	while (src[i] != '\0' && size != 0 && size_dest + i < size - 1)
	{
		dest[size_dest + i] = src[i];
		i++;
	}
	dest[size_dest + i] = '\0';
	return (size_dest + size_src);
}
/*
int main() {
    char dest[20] = "Hello ";
    const char src[] = "World!";
    printf("Total Length dest: %d\n", strlen(dest));
    size_t result = ft_strlcat(dest, src,12);

    printf("Concatenated String: %s\n", dest);
    printf("Total Length: %zu\n", result);
    printf("Total Length dest: %d\n", strlen(dest));
    printf("Total Length src: %d\n", strlen(src));
    return 0;
}
*/
