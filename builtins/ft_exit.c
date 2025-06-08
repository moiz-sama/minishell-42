/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 17:59:35 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/15 18:00:09 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_it(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(2);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_check(char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num *= 10;
		num += str[i] - '0';
		if (num < 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(t_mini *data, t_env *envp)
{
	unsigned int	num;

	num = 0;
	if (!data->command[1])
		exit(envp->exit_status);
	if (!is_number(data->command[1]))
	{
		if (data->command[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		if (ft_check(data->command[1]))
			print_it(data->command[1]);
		num = (unsigned int)ft_atoi(data->command[1]);
		exit (num);
	}
	else
		print_it(data->command[1]);
	return (0);
}

char	*get_pwd(t_list *env, char *str, int plus)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, plus) == 0)
			return (ft_strdup(tmp->content + plus));
		tmp = tmp->next;
	}
	return (NULL);
}
