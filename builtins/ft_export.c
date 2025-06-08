/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:50:16 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/21 14:33:48 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*add_to_list(t_list *list, char *var)
{
	char	*var_name;
	t_list	*new;

	var_name = get_var_name(var);
	remove_old_var(&list, var_name);
	new = ft_lstnew(ft_strdup(var));
	if (!new)
	{
		free(var_name);
		return (NULL);
	}
	ft_lstadd_back(&list, new);
	free(var_name);
	return (list);
}

static void	handle_sum(t_mini *data, t_env *envp, int i)
{
	if (!check_sum(data->command[i], envp->export_list)
		|| !check_sum(data->command[i], envp->env_list))
	{
		data->command[i] = remove_sum(data->command[i]);
		envp->export_list = add_to_list(envp->export_list, data->command[i]);
		envp->env_list = add_to_list(envp->env_list, data->command[i]);
	}
}

static void	check_it2(t_mini *data, t_env *envp)
{
	int	i;

	i = 1;
	while (data->command[i])
	{
		if (!ft_isalpha(data->command[i][0]) || is_valid2(data->command[i]))
		{
			ft_putstr_fd(data->command[i], 2);
			ft_putendl_fd(" : not a valid identifier", 2);
			envp->exit_status = 1;
		}
		else if (get_sum(data->command[i]))
			handle_sum(data, envp, i);
		else if (!ft_strchr(data->command[i], '='))
			envp->export_list = add_to_list(envp->export_list,
					data->command[i]);
		else
		{
			envp->env_list = add_to_list(envp->env_list, data->command[i]);
			envp->export_list = add_to_list(envp->export_list,
					data->command[i]);
		}
		i++;
	}
}

int	ft_export(t_mini *data, t_env *envp, int w_fd)
{
	if (data->command[1])
		check_it2(data, envp);
	else
	{
		ft_sorting(envp->export_list);
		ft_only_export(envp->export_list, w_fd);
		envp->exit_status = 0;
	}
	return (envp->exit_status);
}
