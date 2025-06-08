/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:00:33 by saderdou          #+#    #+#             */
/*   Updated: 2024/08/19 12:00:36 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_mini	*get_list_of_cmds(char **splited)
{
	int		i;
	t_mini	*input;
	t_mini	*new_input;

	i = -1;
	input = NULL;
	while (splited[++i])
	{
		new_input = malloc(sizeof(t_mini));
		if (!new_input)
			return (free_splited(splited), NULL);
		new_input->command = NULL;
		new_input->red = NULL;
		new_input->next = NULL;
		if (!get_list_and_cmds(new_input, splited[i]))
			return (free(new_input), free_splited(splited), NULL);
		lstadd__back(&input, new_input);
	}
	return (free_splited(splited), input);
}

static void	replace_special_chars(char *p_to_char)
{
	if (*p_to_char == S_QUOTES)
		*p_to_char = 39;
	else if (*p_to_char == D_QUOTES)
		*p_to_char = '"';
	else if (*p_to_char == SPACES)
		*p_to_char = ' ';
	else if (*p_to_char == IN_RED)
		*p_to_char = '<';
	else if (*p_to_char == OUT_RED)
		*p_to_char = '>';
}

static int	for_list(t_red *list, int x)
{
	char	**str;

	while (list)
	{
		if (list->input)
			str = &(list->input);
		else if (list->out)
			str = &(list->out);
		else if (list->limiter)
			str = &(list->limiter);
		else
			return (1);
		x = -1;
		while ((*str)[++x])
			replace_special_chars(&((*str)[x]));
		list = list->next;
	}
	return (1);
}

int	quotes_cases_2(t_mini *input)
{
	int		i;
	int		x;

	while (input)
	{
		if (input->command)
		{
			i = -1;
			while (input->command[++i])
			{
				x = -1;
				while (input->command[i][++x])
					replace_special_chars(&(input->command[i][x]));
			}
		}
		if (!for_list(input->red, 0))
			return (0);
		input = input->next;
	}
	return (1);
}

t_mini	*ft_parsing(char *str, t_env *hold)
{
	char	**splited;
	t_mini	*data;

	if (str[0] == 0)
		return (NULL);
	splited = ft_split_pipe(str, hold);
	if (!splited)
		return (NULL);
	else
	{
		quotes_cases_1(splited);
		data = get_list_of_cmds(splited);
		if (!data)
			ft_error("data = NULL (parsing)\n");
		quotes_cases_2(data);
	}
	ft_expand(data, hold);
	return (data);
}
