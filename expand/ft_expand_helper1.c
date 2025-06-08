/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_helper1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:29:42 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/22 12:41:33 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid(char *str)
{
	int	i;

	if (!ft_isalpha(str[1]))
		return (0);
	i = 2;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	remove_spaces(char *str)
{
	int	i;
	int	j;
	int	space_found;

	i = 0;
	j = 0;
	space_found = 0;
	while (str[i])
	{
		if (!isspace((unsigned char)str[i]))
		{
			str[j++] = str[i];
			space_found = 0;
		}
		else if (!space_found)
		{
			str[j++] = ' ';
			space_found = 1;
		}
		i++;
	}
	if (j > 0 && str[j - 1] == ' ')
		j--;
	str[j] = '\0';
}

char	*l_qoutes(char *str, int c)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*get_var_name1(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*check_it(char *str, t_list *lst)
{
	t_list	*current;
	char	*tmp_str;
	char	*s;

	current = lst;
	while (str && current)
	{
		tmp_str = get_var_name1((char *)current->content);
		if (ft_strcmp(str, tmp_str) == 0)
		{
			free(tmp_str);
			s = ft_strchr((char *)current->content, '=');
			if (s)
				return (ft_strdup(s + 1));
		}
		free(tmp_str);
		current = current->next;
	}
	return (NULL);
}
