/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helpe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:25:17 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/18 10:29:24 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	safe_close(int fd)
{
	if (fd >= 0)
		close(fd);
	return ;
}

void	free_prev(int **tab, int index)
{
	while (index >= 0)
	{
		safe_close(tab[index][0]);
		safe_close(tab[index][1]);
		free(tab[index]);
		index--;
	}
	free(tab);
	return ;
}

int	**create_pipes(int count)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * (count));
	if (!pipes)
		return (NULL);
	pipes[count - 1] = NULL;
	while (i < count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			free_prev(pipes, i);
			return (0);
		}
		i++;
	}
	return (pipes);
}

void	close_unused_pipes(int **pipes, int w_fd, int r_fd)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		if (pipes[i][0] != r_fd)
			safe_close(pipes[i][0]);
		if (pipes[i][1] != w_fd)
			safe_close(pipes[i][1]);
		i++;
	}
}

void	close_and_free_pipes(int **fds)
{
	int	i;

	i = 0;
	if (!fds)
		return ;
	while (fds[i])
	{
		safe_close(fds[i][1]);
		safe_close(fds[i][0]);
		free(fds[i]);
		i++;
	}
	free(fds);
	fds = NULL;
}
