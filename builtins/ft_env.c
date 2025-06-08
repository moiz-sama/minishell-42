/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:01:39 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/15 17:40:28 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_mini *data, t_env *envp, int w_fd, int r_fd)
{
	t_list	*head;

	head = envp->env_list;
	while (head)
	{
		if (ft_strncmp(head->content, TEMP_PATH, ft_strlen(TEMP_PATH)) == 0)
		{
			head = head->next;
			continue ;
		}
		if (ft_strncmp(head->content, "OLDPWD", 7) == 0)
		{
			head = head->next;
			continue ;
		}
		ft_putendl_fd(head->content, w_fd);
		head = head->next;
	}
	(void)r_fd;
	(void)data;
	return ;
}

void	update_help(char **ptr, char *temp)
{
	free(*ptr);
	*ptr = ft_strdup(temp);
	free(temp);
	return ;
}
