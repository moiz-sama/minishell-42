/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:03:59 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/29 18:04:02 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status->status = 130;
}

void	shell_signals(void)
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	new_line(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_status->status = 130;
}

void	quit_coredump(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	g_status->status = 131;
}

void	x(int c)
{
	(void)c;
	write(1, "\n", 1);
	exit(130);
}
