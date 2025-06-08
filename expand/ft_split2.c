/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:24:29 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/22 15:59:58 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	words_cnt2(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c && isnt(s, i))
			i++;
		else
		{
			cnt++;
			while (s[i] && (s[i] != c || !isnt(s, i)))
				i++;
		}
	}
	return (cnt);
}

static char	**ft_free22(char **str, int i)
{
	while (i > 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	*ft_fill2(char *ptr, char const *s, int j, int wl)
{
	int	i;

	i = 0;
	while (wl > 0)
	{
		ptr[i] = s[j - wl];
		i++;
		wl--;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**split_words2(char const *s, char **str, char c, int wc)
{
	int	i;
	int	word;
	int	wl;

	i = 0;
	word = 0;
	wl = 0;
	while (word < wc)
	{
		while (s[i] && s[i] == c && isnt(s, i))
			i++;
		while (s[i] && (s[i] != c || !isnt(s, i)))
		{
			wl++;
			i++;
		}
		str[word] = (char *)malloc(sizeof(char) * (wl + 1));
		if (!str[word])
			return (ft_free22(str, word));
		ft_fill2(str[word], s, i, wl);
		wl = 0;
		word++;
	}
	str[word] = 0;
	return (str);
}

char	**ft_split2(char const *s, char c)
{
	int		wc;
	char	**str;

	wc = 0;
	if (!s)
		return (NULL);
	wc = words_cnt2(s, c);
	str = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!str)
		return (NULL);
	str = split_words2(s, str, c, wc);
	return (str);
}
