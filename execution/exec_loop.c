/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:50:13 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/17 10:03:15 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ignore_signals(t_mini *data)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, quit_coredump);
	if (data && data->command && data->command[0]
		&& !ft_strncmp(g_status->prog_name, data->command[0],
			ft_strlen(data->command[0]) + 1))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	ft_dup(int *w_fd, int *r_fd)
{
	if (*w_fd >= 0)
	{
		if (dup2(*w_fd, STDOUT_FILENO) == -1)
			perror("dup2");
		safe_close(*w_fd);
	}
	if (*r_fd >= 0)
	{
		if (dup2(*r_fd, STDIN_FILENO) == -1)
			perror("dup2");
		safe_close(*r_fd);
	}
}

int	exec_child(t_mini *data, t_env *hold, int w_fd, int r_fd)
{
	int		exit_status;
	char	*cmd_path;

	close_unused_pipes(hold->pipes, w_fd, r_fd);
	if (check_builtin(data) == 1)
	{
		exit_status = exec_builtin(data, hold, w_fd, r_fd);
		return (exit_status);
	}
	ft_dup(&w_fd, &r_fd);
	exit_status = redirecte(data->red);
	if (exit_status)
		return (exit_status);
	cmd_path = find_path(data, hold);
	exit_status = exit_errors(cmd_path);
	if (exit_status)
		return (free(cmd_path), exit_status);
	if (data->command == NULL || !data->command[0])
		return (exit_status);
	execve(cmd_path, data->command, hold->env_arr);
	ft_putstr_fd(data->command[0], 2);
	write(2, ": command not found\n", 20);
	free(cmd_path);
	return (127);
}

int	executer(t_mini *data, t_env *hold, int w_fd, int r_fd)
{
	int	pid;
	int	exit_status;

	if (check_builtin(data) == 1 && hold->count == 1)
	{
		exit_status = exec_builtin(data, hold, w_fd, r_fd);
		pid = fork();
		if (pid == 0)
			exit(exit_status);
		return (pid);
	}
	ignore_signals(data);
	pid = fork();
	if (pid == 0)
	{
		hold->env_arr = get_arr(hold->env_list);
		exit_status = exec_child(data, hold, w_fd, r_fd);
		free_splited(hold->env_arr);
		exit(exit_status);
	}
	return (safe_close(w_fd), safe_close(r_fd), pid);
}

int	exec_loop(t_mini *head, t_env *hold, int count)
{
	int		np;
	int		pid;

	np = 1;
	hold->count = count;
	if (count == 1)
	{
		hold->pipes = NULL;
		pid = executer(head, hold, -1, -1);
		return (pid);
	}
	hold->pipes = create_pipes(count);
	executer(head, hold, hold->pipes[0][1], -1);
	head = head->next;
	while (head->next)
	{
		executer(head, hold, hold->pipes[np][1], hold->pipes[np - 1][0]);
		np++;
		head = head->next;
	}
	pid = executer(head, hold, -1, hold->pipes[count - 2][0]);
	close_and_free_pipes(hold->pipes);
	return (pid);
}
