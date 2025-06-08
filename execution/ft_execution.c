/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:33:51 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/17 18:41:43 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_pipes(t_mini *data)
{
	int		i;
	t_mini	*head;

	head = data;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	herdoc_fork(t_mini *data, t_env *hold)
{
	int	exit_status;

	exit_status = 0;
	handle_herdoc(data, hold);
	return (exit_status);
}

int	ft_execution(t_mini *data, t_env *hold)
{
	int	count;
	int	last_pid;
	int	exit_status;

	if (herdoc_exist(data) != 0)
	{
		if (herdoc_exist(data) >= 17)
			return (pt(" maximum here-document count exceeded\n"), 2);
		herdoc_fork(data, hold);
		if (hold->exit_status != 0)
			return (hold->exit_status);
	}
	count = ft_count_pipes(data);
	last_pid = exec_loop(data, hold, count);
	waitpid(last_pid, &exit_status, 0);
	while (wait(NULL) != -1)
	{
	}
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	return (exit_status);
}
