/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:38:58 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/13 20:11:49 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	out_put_red_and_append(char *str, int *i)
{
	int	checker;

	(*i)++;
	checker = 0;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] != ' ' && str[*i] != '>'
			&& str[*i] != '<')
		{
			checker = 1;
			break ;
		}
		if (str[*i] == '>' || str[*i] == '<')
			return (0);
		(*i)++;
	}
	if (!checker)
		return (0);
	return (1);
}

int	input_red_and_her_doc(char *str, int *i)
{
	int	checker;

	checker = 0;
	(*i)++;
	if (str[*i] == '>' || str[*i] == '<')
		(*i)++;
	while (str[*i] && str[*i] != '|')
	{
		if (str[*i] != ' ' && str[*i] != '>'
			&& str[*i] != '<')
		{
			checker = 1;
			break ;
		}
		if (str[*i] == '>' || str[*i] == '<')
			return (0);
		(*i)++;
	}
	if (!checker)
		return (0);
	return (1);
}

void	skip(char *str, int *i)
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

int	redirection_errors(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip(str, &i);
		if (str[i] == '>' && str[i + 1] != '>')
		{
			if (!out_put_red_and_append(str, &i))
				return (0);
		}
		else if (str[i] == '<')
		{
			if (!input_red_and_her_doc(str, &i))
				return (0);
		}
		else if (ft_strncmp(&str[i], ">>>", 3) == 0)
			return (0);
		else
			i++;
	}
	return (1);
}
