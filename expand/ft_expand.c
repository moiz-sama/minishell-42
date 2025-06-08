/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:13:20 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/25 20:37:57 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_j(char **command, int *tab, char *tmp, t_env *envp)
{
	char	*value;
	int		len;

	value = check_it(tmp, envp->env_list);
	if (value)
	{
		len = ft_strlen(value);
		do_it(command, tab[0], tab[1], value);
		tab[0] += len - 1;
	}
	else
	{
		do_it(command, tab[0], tab[1], ft_strdup(""));
		tab[0] -= 1;
	}
	return (tab[0]);
}

void	expand_variables(char **command, t_env *envp)
{
	int		tab[2];
	int		flag;
	char	*tmp;

	flag = 0;
	tab[0] = 0;
	while ((*command) && (*command)[tab[0]])
	{
		define_flag((*command)[tab[0]], &flag);
		if ((*command)[tab[0]] == '$' && is_valid_key(&(*command)[tab[0] + 1])
			&& (*command)[tab[0] + 1] != '?' && flag != 2)
		{
			tab[1] = tab[0] + 1;
			while ((*command)[tab[1]] && ft_isalnum((*command)[tab[1]]))
				tab[1]++;
			tmp = ft_substr((*command), tab[0] + 1, tab[1] - (tab[0] + 1));
			if (tmp && tmp[0])
				tab[0] = handle_j(&(*command), tab, tmp, envp);
			free(tmp);
		}
		else if (flag != 2)
			hanle_status(&(*command), envp, tab[0]);
		tab[0]++;
	}
}

char	**split_commands(char **commands)
{
	char	**s1;
	char	**s2;
	int		i;
	int		r;

	s1 = NULL;
	s2 = NULL;
	i = 0;
	r = 0;
	while (commands && commands[i])
	{
		s1 = ft_split2(commands[i], ' ');
		if (!s1)
			return (NULL);
		while (s1[r])
		{
			s2 = new_arr(s2, s1[r]);
			r++;
		}
		r = 0;
		ft_free(s1);
		i++;
	}
	return (s2);
}

void	ft_expand2(t_mini *data, t_env *envp)
{
	int		i;
	char	**new_commands;

	i = 0;
	if (!data || !data->command)
		return ;
	while (data->command[i])
	{
		expand_variables(&data->command[i], envp);
		i++;
	}
	new_commands = split_commands(data->command);
	ft_free(data->command);
	data->command = new_commands;
	remove_quotes2(data->command);
	ft_expand_red(data, envp);
}

void	ft_expand(t_mini *data, t_env *envp)
{
	t_mini	*tmp;

	tmp = data;
	while (tmp)
	{
		ft_expand2(tmp, envp);
		tmp = tmp->next;
	}
}
