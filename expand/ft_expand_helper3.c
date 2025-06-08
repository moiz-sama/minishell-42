/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_helper3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:29:26 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/22 16:00:05 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hanle_status(char **s, t_env *envp, int index)
{
	char	*tmp;
	char	*status;
	char	*new_s;
	char	*before;
	char	*after;

	if (*s && ft_strncmp(&(*s)[index], "$?", 2) == 0)
	{
		status = ft_itoa(envp->exit_status);
		before = ft_substr(*s, 0, index);
		after = ft_strdup(&(*s)[index + 2]);
		tmp = ft_strjoin(before, status);
		new_s = ft_strjoin(tmp, after);
		free(*s);
		*s = ft_strdup(new_s);
		free(status);
		free(before);
		free(after);
		free(tmp);
		free(new_s);
	}
}

int	is_valid_key(char *key)
{
	if (!*key)
		return (0);
	return (1);
}

void	remove_quotes2(char **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
	{
		commands[i] = mssa7(commands[i]);
		i++;
	}
}

int	isnt(char const *s, int index)
{
	int	flag_s;
	int	flag_d;
	int	i;

	flag_s = 0;
	flag_d = 0;
	i = 0;
	while (s[i])
	{
		if (!flag_d && s[i] == '"')
			flag_d = 1;
		else if (flag_d && s[i] == '"')
			flag_d = 0;
		if (!flag_s && s[i] == '\'')
			flag_s = 1;
		else if (flag_s && s[i] == '\'')
			flag_s = 0;
		if (!flag_d && !flag_s && i == index)
			return (1);
		i++;
	}
	return (0);
}
