/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:14:48 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/13 20:14:51 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cpy(char *splited, int *i, char *str, int *x)
{
	while (splited[*i] && splited[*i] != ' ' && splited[*i] != '>'
		&& splited[*i] != '<')
	{
		str[(*x)++] = splited[*i];
		splited[(*i)++] = ' ';
	}
	str[(*x)++] = 0;
}

int	quotes_cases_1(char **splited)
{
	int		i;
	int		x;

	i = -1;
	while (splited[++i])
	{
		x = 0;
		while (splited[i][x])
		{
			if (splited[i][x] == 39)
				case_of_single_quotes(splited[i], &x);
			else if (splited[i][x] == '"')
				case_of_double_quotes(splited[i], &x);
			x++;
		}
	}
	return (1);
}

void	case_of_single_quotes(char *splited, int *x)
{
	splited[(*x)++] = 39;
	while (splited[*x] != 39)
	{
		if (splited[*x] == ' ')
			splited[*x] = SPACES;
		else if (splited[*x] == '"')
			splited[*x] = D_QUOTES;
		else if (splited[*x] == '<')
			splited[*x] = IN_RED;
		else if (splited[*x] == '>')
			splited[*x] = OUT_RED;
		(*x)++;
	}
	splited[*x] = 39;
}

void	case_of_double_quotes(char *splited, int *x)
{
	splited[(*x)++] = '"';
	while (splited[*x] != '"')
	{
		if (splited[*x] == 39)
			splited[*x] = S_QUOTES;
		else if (splited[*x] == ' ')
			splited[*x] = SPACES;
		else if (splited[*x] == '<')
			splited[*x] = IN_RED;
		else if (splited[*x] == '>')
			splited[*x] = OUT_RED;
		(*x)++;
	}
	splited[*x] = '"';
}
