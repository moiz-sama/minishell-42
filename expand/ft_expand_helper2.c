/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:29:42 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/22 14:13:42 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

int	do_it(char **command, int j, int k, char *value)
{
	char	*first;
	char	*new;
	char	*rest;

	first = ft_substr(*command, 0, j);
	if (!first)
		return (free(value), 0);
	new = ft_strjoin(first, value);
	free(first);
	if (!new)
		return (free(value), 0);
	rest = ft_strdup(*command + k);
	if (!rest)
		return (free(value), free(new), 0);
	free(*command);
	*command = ft_strjoin(new, rest);
	return (free(value), free(new), free(rest), 0);
}

void	define_flag(char c, int *flag)
{
	if (c == 39 && *flag == 0)
		*flag = 2;
	else if (c == 39 && *flag == 2)
		*flag = 0;
	if (c == 34 && *flag == 0)
		*flag = 1;
	else if (c == 34 && *flag == 1)
		*flag = 0;
}

char	*mssa7(char *str)
{
	int		i;
	int		j;
	char	*new;
	int		s_qoutes;
	int		d_qoutes;

	i = 0;
	j = 0;
	s_qoutes = 0;
	d_qoutes = 0;
	new = malloc(strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !s_qoutes)
			d_qoutes = !d_qoutes;
		else if (str[i] == '\'' && !d_qoutes)
			s_qoutes = !s_qoutes;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (free(str), new);
}

char	**new_arr(char **s2, char *str)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	j = 0;
	if (s2)
	{
		while (s2[i])
			i++;
	}
	new_arr = (char **)malloc((i + 2) * sizeof(char *));
	while (j < i)
	{
		new_arr[j] = s2[j];
		j++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	free(s2);
	return (new_arr);
}
