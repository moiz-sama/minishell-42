/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_initial.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:39:00 by saderdou          #+#    #+#             */
/*   Updated: 2024/08/24 10:39:07 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *envp)
{
	t_list	*current;
	t_list	*next;

	current = envp->env_list;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	current = envp->export_list;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	free(envp);
}

void	free_list_red(t_red *list)
{
	t_red	*next;

	while (list)
	{
		free(list->input);
		free(list->out);
		free(list->limiter);
		next = list->next;
		free(list);
		list = next;
	}
}

void	free_list(t_mini *data)
{
	int		i;
	t_mini	*next_data;

	while (data)
	{
		if (data->command)
		{
			i = 0;
			while (data->command[i])
				free(data->command[i++]);
			free(data->command);
		}
		free_list_red(data->red);
		next_data = data->next;
		free(data);
		data = next_data;
	}
}
