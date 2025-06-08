/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:43:22 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/17 11:43:23 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_access(char **env)
{
	t_list	*head;
	t_list	*tmp;
	int		i;

	i = 1;
	head = ft_lstnew(ft_strdup(env[0]));
	tmp = head;
	while (env[i])
	{
		tmp->next = ft_lstnew(ft_strdup(env[i]));
		i++;
		tmp = tmp->next;
	}
	return (head);
}

char	*ft_init_pwd(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (ft_strdup(env[i] + 4));
		i++;
	}
	return (ft_strdup(""));
}

char	**ft_env_arr(t_env *hold)
{
	char	**env;
	char	*str;

	env = malloc(sizeof(char *) * 6);
	str = getcwd(NULL, 0);
	if (str == NULL)
	{
		perror("");
		str = "\0";
	}
	env[0] = ft_strjoin("PWD=", str);
	env[1] = ft_strdup("SHLVL=0");
	env[2] = ft_strdup(TEMP_PATH);
	env[3] = ft_strdup("OLDPWD");
	env[4] = ft_strdup("_=/usr/bin/env");
	env[5] = NULL;
	hold->pwd = ft_strdup(str);
	return (free(str), env);
}

void	init_env(t_env *envp, char **env)
{
	char	**env_arr;

	if (!env[0])
	{
		env_arr = ft_env_arr(envp);
		envp->env_list = ft_access(env_arr);
		envp->export_list = ft_access(env_arr);
		free_splited(env_arr);
	}
	else
	{
		envp->env_list = ft_access(env);
		envp->export_list = ft_access(env);
		envp->pwd = ft_init_pwd(env);
	}
	return ;
}
