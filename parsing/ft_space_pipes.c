/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:03:40 by saderdou          #+#    #+#             */
/*   Updated: 2024/08/20 12:03:44 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		else if (str[i] == 39)
		{
			i++;
			while (str[i] != 39)
				i++;
		}
		else if ((str[i] >= 9 && str[i] <= 13)
			|| str[i] == 32)
			str[i] = ' ';
		i++;
	}
}

char	*do_space(char *s)
{
	int		len;
	char	*new;
	int		i;

	i = 0;
	if (!syntax_error(s))
		return (NULL);
	white_spaces(s);
	while (s[i] == ' ' && s[i])
		i++;
	if (!s[i])
		return (NULL);
	len = ft_strlen(s) * 2 + 1;
	new = malloc(len);
	if (!new)
		return (NULL);
	get_new(s, new);
	return (new);
}

char	*ft_space_and_pipes(char *str, t_env *hold)
{
	char	*new;

	new = do_space(str);
	if (!new)
		return (NULL);
	if (!ft_error_pipe(new))
	{
		ft_error(" syntax error pipe \n");
		free(new);
		hold->exit_status = 2;
		return (NULL);
	}
	if (!redirection_errors(new))
	{
		ft_error(" syntax error red \n");
		free(new);
		hold->exit_status = 2;
		return (NULL);
	}
	return (new);
}
