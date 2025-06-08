/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:14:24 by saderdou          #+#    #+#             */
/*   Updated: 2024/08/19 12:14:27 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *read_line, int i)
{
	if (read_line[i] == 39)
	{
		i++;
		while (read_line[i] != 39 && read_line[i])
			i++;
		if (!read_line[i])
			return (-1);
	}
	else if (read_line[i] == '"')
	{
		i++;
		while (read_line[i] != '"' && read_line[i])
			i++;
		if (!read_line[i])
			return (-1);
	}
	return (i);
}

int	syntax_error(char *read_line)
{
	int	i;
	int	checker;

	i = 0;
	while (read_line[i])
	{
		checker = 1;
		i = check_quotes(read_line, i);
		if (i == -1)
		{
			checker = 0;
			break ;
		}
		i++;
	}
	if (checker == 0)
	{
		ft_error("Syntax error quotes\n");
		g_status->status = 2;
		return (0);
	}
	return (1);
}

int	skip_quotes(char *s, char *new, int i, int *j)
{
	if (s[i] == 39)
	{
		if (i && (s[i - 1] == ' '))
			new[(*j)++] = ' ';
		new[(*j)++] = s[i++];
		while (s[i] && s[i] != 39)
			new[(*j)++] = s[i++];
		if (s[i] && s[i] == 39)
			new[(*j)++] = 39;
	}
	else if (s[i] == '"')
	{
		if (i && (s[i - 1] == ' '))
			new[(*j)++] = ' ';
		new[(*j)++] = s[i++];
		while (s[i] && s[i] != '"')
			new[(*j)++] = s[i++];
		if (s[i] && s[i] == '"')
			new[(*j)++] = '"';
	}
	return (i + 1);
}

void	handle_special_chars(char *s, char *new, int *i, int *j)
{
	if (s[*i] != '<' && s[*i] != '>' && s[*i] != ' ')
	{
		if (*i && s[*i - 1] && ((s[*i - 1] == ' ') || s[*i - 1] == '|'
				|| (s[*i - 1] == '<' || s[*i - 1] == '>')))
			new[(*j)++] = ' ';
		new[(*j)++] = s[*i];
	}
	else if (s[*i] && (s[*i] == '<' || s[*i] == '>'))
	{
		if (*i && s[*i - 1] && s[*i - 1] != '<' && s[*i - 1] != '>')
			new[(*j)++] = ' ';
		new[(*j)++] = s[*i];
	}
	(*i)++;
}

void	get_new(char *s, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == ' ')
		i++;
	while (s && s[i])
	{
		if (s[i + 1] && (s[i] == 39 || s[i] == '"'))
		{
			if (i && s[i - 1] && (s[i - 1] == '>' || s[i - 1] == '<'))
			{
				new[j++] = ' ';
			}
			i = skip_quotes(s, new, i, &j);
			if (s[i] && (s[i] == '>' || s[i] == '<'))
				new[j++] = ' ';
		}
		else
			handle_special_chars(s, new, &i, &j);
	}
	new[j] = '\0';
	return ;
}
