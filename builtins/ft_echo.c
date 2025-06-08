/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:44:00 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/17 18:36:06 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	ft_echo(t_mini *data, t_env *envp, int w_fd, int r_fd)
{
	int	i;
	int	v;
	int	flag;

	v = 0;
	flag = 0;
	i = 1;
	while (data->command[i] && check_option(data->command[i]))
	{
		v = 1;
		i++;
	}
	while (data->command[i])
	{
		if (flag)
			ft_putstr_fd(" ", w_fd);
		ft_putstr_fd(data->command[i], w_fd);
		flag = 1;
		i++;
	}
	if (!v)
		ft_putstr_fd("\n", w_fd);
	(void)r_fd;
	(void)envp;
}
