/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:32:25 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/17 11:39:39 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_mini *data)
{
	if (data->command == NULL)
		return (0);
	if (ft_strncmp(data->command[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(data->command[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(data->command[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(data->command[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(data->command[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(data->command[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(data->command[0], "export", 7) == 0)
		return (1);
	return (0);
}

int	check_open2(t_red *red, int *in, int *out)
{
	if (red->who == INPUT_RD)
	{
		if (red->input == NULL)
			return (1);
		*in = open(red->input, O_RDONLY);
	}
	else if (red->who == RD_TRNC)
	{
		if (red->out == NULL)
			return (1);
		*out = open(red->out, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
	else if (red->who == RD_APND)
	{
		if (red->out == NULL)
			return (1);
		*out = open(red->out, O_WRONLY | O_CREAT | O_APPEND, 0664);
	}
	return (0);
}

int	redirecte_builtin(t_red *red, int *w_fd)
{
	int	out;
	int	in;

	out = 0;
	in = 0;
	while (red)
	{
		if (check_open2(red, &in, &out) == 1)
			return (1);
		if (in == -1)
			return (pt(red->input), perror(" "), 1);
		if (out == -1)
			return (pt(red->out), perror(" "), 1);
		if (out > 0)
			*w_fd = out;
		red = red->next;
	}
	return (0);
}

int	exec_builtin(t_mini *data, t_env *envp, int w_fd, int r_fd)
{
	int	exit_status;

	if (w_fd == -1)
		w_fd = 1;
	exit_status = redirecte_builtin(data->red, &w_fd);
	if (exit_status)
		return (exit_status);
	if (ft_strncmp(data->command[0], "pwd", 4) == 0)
		return (ft_pwd(data, envp, w_fd, r_fd));
	else if (ft_strncmp(data->command[0], "cd", 3) == 0)
		return (ft_cd(data, envp));
	else if (ft_strncmp(data->command[0], "echo", 5) == 0)
		return (ft_echo(data, envp, w_fd, r_fd), 0);
	else if (ft_strncmp(data->command[0], "exit", 5) == 0)
		return (ft_exit(data, envp));
	else if (ft_strncmp(data->command[0], "env", 4) == 0)
		return (ft_env(data, envp, w_fd, r_fd), 0);
	else if (ft_strncmp(data->command[0], "unset", 6) == 0)
		return (ft_unset(data, envp), 0);
	else if (ft_strncmp(data->command[0], "export", 7) == 0)
		return (ft_export(data, envp, w_fd));
	return (0);
}
