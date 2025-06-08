/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:21:10 by saderdou          #+#    #+#             */
/*   Updated: 2024/08/19 22:21:22 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quots(char *str, int *i)
{
	if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '"')
			(*i)++;
	}
	else if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] && str[*i] != 39)
			(*i)++;
	}
}

int	contains_double_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		skip_quots(s, &i);
		if (s[i] == '|')
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '|')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	ends_with_pipe(char *s)
{
	size_t	i;
	int		i1;
	int		i2;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
		{
			if (s[i + 1] == '\0')
				return (1);
			i1 = i - 1;
			i2 = i + 1;
			while (i1 >= 0 && s[i1] == ' ')
				i1--;
			while (s[i2] == ' ')
				i2++;
			if (i1 < 0 || s[i2] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_error_pipe(char *s)
{
	if (s[0] == '|')
		return (0);
	if (contains_double_pipe(s))
		return (0);
	if (ends_with_pipe(s))
		return (0);
	return (1);
}
