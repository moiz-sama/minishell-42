/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:53:17 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/15 17:58:15 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_sum(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	remove_old_var(t_list **list, char *var_name)
{
	t_list	*prev;
	t_list	*current;
	char	*current_name;

	prev = NULL;
	current = *list;
	while (current)
	{
		current_name = get_var_name((char *)current->content);
		if (ft_strcmp(var_name, current_name) == 0)
		{
			free(current_name);
			if (prev)
				prev->next = current->next;
			else
				*list = current->next;
			free(current->content);
			free(current);
			return ;
		}
		free(current_name);
		prev = current;
		current = current->next;
	}
}

int	is_valid2(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '=')
		&& str[i])
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

t_list	*update_value(t_list *lst, char *str, int k, int i)
{
	char	*content;
	char	*new_value;

	while (lst)
	{
		content = (char *)lst->content;
		if (ft_strncmp(str, content, i) == 0)
		{
			while (str[k] != '=')
				k++;
			new_value = ft_strjoin(content, str + k + 1);
			if (new_value)
			{
				free(lst->content);
				lst->content = new_value;
			}
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}

t_list	*check_sum(char *str, t_list *lst)
{
	int		i;
	int		k;	

	i = 0;
	k = 0;
	while (str && str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (update_value(lst, str, k, i));
		i++;
	}
	return (NULL);
}
