/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:08:46 by saderdou          #+#    #+#             */
/*   Updated: 2024/08/19 12:08:50 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_of_pipe_inside_quotes_1(char *read_line)
{
	int	i;

	i = -1;
	while (read_line[++i])
	{
		if (read_line[i] == '"')
		{
			while (read_line[++i] != '"')
			{
				if (read_line[i] == '|')
					read_line[i] = -1;
			}
		}
		else if (read_line[i] == 39)
		{
			while (read_line[++i] != 39)
			{
				if (read_line[i] == '|')
					read_line[i] = -1;
			}
		}
	}
}

void	case_of_pipe_inside_quotes_2(char **splited)
{
	int	i;
	int	x;

	i = -1;
	while (splited[++i])
	{
		x = -1;
		while (splited[i][++x])
		{
			if (splited[i][x] == -1)
				splited[i][x] = '|';
		}
	}
}

char	**ft_split_pipe(char *str, t_env *hold)
{
	char	**splited;
	char	*new;

	new = ft_space_and_pipes(str, hold);
	if (!new)
		return (NULL);
	case_of_pipe_inside_quotes_1(new);
	splited = ft_split(new, '|');
	case_of_pipe_inside_quotes_2(splited);
	free(new);
	return (splited);
}
