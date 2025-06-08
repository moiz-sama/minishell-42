/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:33:51 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/18 10:21:39 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*get_secure_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char **path_splited, char *cmd)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	tmp = NULL;
	str = NULL;
	while (path_splited[i])
	{
		str = ft_strjoin(path_splited[i], "/");
		tmp = ft_strjoin(str, cmd);
		free(str);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
		free(tmp);
	}
	return (NULL);
}

char	*get_cmd_with_path(char *cmd, char **env)
{
	char	*secure_path;
	char	**path_splited;
	char	*cmd_with_path;

	secure_path = get_secure_path(env);
	if (!secure_path)
		return (NULL);
	path_splited = ft_split(secure_path, ':');
	free(secure_path);
	cmd_with_path = get_cmd_path(path_splited, cmd);
	free_splited(path_splited);
	return (cmd_with_path);
}

char	*find_path(t_mini *data, t_env *hold)
{
	char	*cmd_path;

	if (data->command == NULL || !data->command[0])
		return (NULL);
	if (data->command[0][0] == '\0')
		return (NULL);
	if (is_path(data->command[0]) == 0)
	{
		cmd_path = get_cmd_with_path(data->command[0], hold->env_arr);
		if (!cmd_path)
			return (data->command[0]);
		return (cmd_path);
	}
	return (data->command[0]);
}
