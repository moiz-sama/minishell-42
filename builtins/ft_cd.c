/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:38:17 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/15 17:38:29 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_export_list(t_env *envp, char *old_pwd, char *new_pwd)
{
	char	*temp;
	t_list	*head;

	temp = NULL;
	head = envp->export_list;
	while (head)
	{
		if (ft_strncmp(head->content, "PWD=", 4) == 0)
		{
			temp = ft_strjoin("PWD=", new_pwd);
			if (temp == NULL)
				temp = ft_strjoin("PWD=", envp->pwd);
			update_help(&(head->content), temp);
		}
		else if (ft_strncmp(head->content, "OLDPWD", 6) == 0)
		{
			temp = ft_strjoin("OLDPWD=", old_pwd);
			if (temp == NULL)
				temp = ft_strdup("OLDPWD");
			update_help(&(head->content), temp);
		}
		head = head->next;
	}
	return ;
}

void	update_envp_list(t_env *envp, char *old_pwd, char *new_pwd)
{
	char	*temp;
	t_list	*head;

	temp = NULL;
	head = envp->env_list;
	while (head)
	{
		if (ft_strncmp(head->content, "PWD=", 4) == 0)
		{
			temp = ft_strjoin("PWD=", new_pwd);
			if (temp == NULL)
				temp = ft_strjoin("PWD=", envp->pwd);
			update_help(&(head->content), temp);
		}
		else if (ft_strncmp(head->content, "OLDPWD", 6) == 0)
		{
			temp = ft_strjoin("OLDPWD=", old_pwd);
			if (temp == NULL)
				temp = ft_strdup("OLDPWD=");
			update_help(&(head->content), temp);
		}
		head = head->next;
	}
	return ;
}

int	ft_cd_help(t_mini *data, t_env *envp)
{
	char	*str1;
	char	*str2;

	if (data->command[2])
		return (ft_putendl_fd("cd: too many arguments", 2), 1);
	if (chdir(data->command[1]) == 0)
	{
		str1 = getcwd(NULL, 0);
		if (str1 == NULL)
			str1 = ft_strdup("0");
		str2 = get_pwd(envp->env_list, "PWD=", 4);
		update_envp_list(envp, str2, str1);
		update_export_list(envp, str2, str1);
		if (envp->pwd)
			free(envp->pwd);
		envp->pwd = ft_strdup(str1);
		return (free(str1), free(str2), 0);
	}
	else
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd_home(t_env *envp)
{
	char	*str1;
	char	*str2;
	char	*tmp;

	tmp = get_pwd(envp->env_list, "HOME=", 5);
	if (tmp == NULL)
	{
		printf("cd: HOME not set\n");
		free (tmp);
		return (1);
	}
	if (chdir(tmp) == 0)
	{
		str1 = getcwd(NULL, 0);
		if (str1 == NULL)
			str1 = ft_strdup("0");
		str2 = get_pwd(envp->env_list, "PWD=", 4);
		update_envp_list(envp, str2, str1);
		update_export_list(envp, str2, str1);
		if (envp->pwd)
			free(envp->pwd);
		envp->pwd = ft_strdup(str1);
		return (free(str1), free(str2), free(tmp), 0);
	}
	return (free (tmp), 0);
}

int	ft_cd(t_mini *data, t_env *envp)
{
	int	exit_status;

	if (data->command[1])
	{
		exit_status = ft_cd_help(data, envp);
		return (exit_status);
	}
	else
	{
		exit_status = ft_cd_home(envp);
		return (exit_status);
	}
	return (0);
}
