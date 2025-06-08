/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:54:32 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/13 18:19:02 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pt(char *str)
{
	ft_putstr_fd(str, 2);
}

int	check_open(t_red *red, int *in, int *out)
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

int	redirecte(t_red *red)
{
	int	out;
	int	in;

	out = 0;
	in = 0;
	while (red)
	{
		if (check_open(red, &in, &out) == 1)
			return (1);
		if (in == -1)
			return (pt(red->input), perror(" "), 1);
		if (out == -1)
			return (pt(red->out), perror(" "), 1);
		if (in > 2)
			dup2(in, STDIN_FILENO);
		if (out > 2)
			dup2(out, STDOUT_FILENO);
		red = red->next;
	}
	return (0);
}
