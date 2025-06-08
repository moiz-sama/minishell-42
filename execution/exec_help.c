/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:59:20 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/18 10:01:45 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_arr(t_list *env)
{
	t_list	*tmp;
	char	**str;
	int		i;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	str = malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		str[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}

int	have_path(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	if (!cmd[0])
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	exit_errors(char *cmd)
{
	struct stat	filetype;

	if (!cmd)
		return (0);
	if (!have_path(cmd) || !cmd[0])
		return (0);
	if (stat(cmd, &filetype) == 0)
	{
		if (S_ISDIR(filetype.st_mode))
		{
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(" : Is a directory", 2);
			return (126);
		}
	}
	else
		return (pt(cmd), perror(" "), 127);
	if (access(cmd, X_OK) != 0)
		return (pt(cmd), perror(" "), 126);
	return (0);
}
