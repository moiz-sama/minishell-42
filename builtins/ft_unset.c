/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:48:47 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/25 19:55:16 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_it(t_list **list, t_list *itr_tmp, t_list *prev)
{
	t_list	*tmp_free;
	t_list	*tmp;

	tmp_free = itr_tmp;
	tmp = itr_tmp->next;
	if (tmp_free == *list)
		*list = tmp;
	else if (prev)
		prev->next = tmp;
	free(tmp_free->content);
	free(tmp_free);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0' && s1[i] != '\0' && s2[i] == s1[i])
		i++;
	return (s1[i] - s2[i]);
}

void	r_node(t_list **list, t_list **itr_tmp, t_list **prev, char *command)
{
	t_list	*next_node;
	char	*tmp;

	next_node = (*itr_tmp)->next;
	tmp = get_var_name((*itr_tmp)->content);
	if (ft_strcmp(command, tmp) == 0)
	{
		remove_it(list, *itr_tmp, *prev);
		*itr_tmp = next_node;
		if (*prev == NULL)
			*prev = *itr_tmp;
	}
	else
	{
		*prev = *itr_tmp;
		*itr_tmp = next_node;
	}
	free(tmp);
	return ;
}

void	ft_unset(t_mini *data, t_env *envp)
{
	int		i;
	t_list	*env_prev;
	t_list	*env_itr_tmp;
	t_list	*export_prev;
	t_list	*export_itr_tmp;

	i = 1;
	env_prev = NULL;
	export_prev = NULL;
	while (data->command[i])
	{
		env_itr_tmp = envp->env_list;
		export_itr_tmp = envp->export_list;
		while (env_itr_tmp || export_itr_tmp)
		{
			if (env_itr_tmp)
				r_node(&envp->env_list, &env_itr_tmp, &env_prev,
					data->command[i]);
			if (export_itr_tmp)
				r_node(&envp->export_list, &export_itr_tmp, &export_prev,
					data->command[i]);
		}
		i++;
	}
}
