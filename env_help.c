/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:38:35 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/29 12:38:39 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_shlvl(int lvl, char *str)
{
	if (lvl < 0)
	{
		lvl = -1;
	}
	if (lvl >= 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putstr_fd(str + 6, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		lvl = 0;
	}
	return (lvl);
}

void	update_shlvl(t_list *envp)
{
	t_list	*tmp;
	int		lvl;
	char	*str;

	tmp = envp;
	lvl = 0;
	while (tmp)
	{
		if (!ft_strncmp("SHLVL=", tmp->content, 6))
		{
			lvl = ft_atoi(tmp->content + 6);
			lvl = check_shlvl(lvl, tmp->content);
			lvl++;
			free(tmp->content);
			str = ft_itoa(lvl);
			tmp->content = ft_strjoin("SHLVL=", str);
			free(str);
			break ;
		}
		tmp = tmp->next;
	}
	return ;
}

void	update_shlvl_export(t_list *export, t_list *envp)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strncmp("SHLVL=", tmp->content, 6))
			break ;
		tmp = tmp->next;
	}
	tmp2 = export;
	while (tmp2)
	{
		if (!ft_strncmp("SHLVL=", tmp2->content, 6))
		{
			free(tmp2->content);
			tmp2->content = ft_strdup(tmp->content);
			break ;
		}
		tmp2 = tmp2->next;
	}
	return ;
}
