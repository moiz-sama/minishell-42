/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:53:54 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/06 09:53:56 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quotes(char *str, int *i, int *j, int *flag)
{
	if (!(*flag) && str[*i] == '=')
	{
		(*j)++;
		str[*j] = '"';
		*flag = 1;
	}
	return (str);
}

char	*ft_do_it(char *str)
{
	int		i;
	int		j;
	int		len;
	int		flag;
	char	*the_new;

	i = 0;
	j = 0;
	len = 0;
	flag = 0;
	while (str[len])
		len++;
	the_new = malloc(len + 3);
	while (str[i])
	{
		the_new[j] = str[i];
		the_new = add_quotes(str, &i, &j, &flag);
		i++;
		j++;
	}
	the_new[j++] = '"';
	the_new[j] = '\0';
	return (the_new);
}

char	*remove_quotes(char *str)
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
		if (str[i] != '"')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*remove_sum(char *str)
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
	while (str && str[i])
	{
		if (str[i] != '+')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	*get_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}
