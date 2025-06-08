/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:59:28 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/21 17:35:52 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_and_copy(char *str)
{
	char	**s1;
	char	**s2;
	int		i;

	s2 = NULL;
	i = 0;
	s1 = ft_split2(str, ' ');
	if (!s1)
		return (NULL);
	while (s1[i])
	{
		s2 = new_arr(s2, s1[i]);
		i++;
	}
	ft_free(s1);
	return (s2);
}

char	*check_for_ambiguity(char **s2)
{
	char	*result;

	if (!s2 || s2[1])
	{
		ft_free(s2);
		return (NULL);
	}
	result = ft_strdup(s2[0]);
	ft_free(s2);
	return (result);
}

char	*ft_expand_red_cr7(char *str, t_env *envp)
{
	char	**s2;
	char	*result;

	s2 = NULL;
	result = NULL;
	if (!str)
		return (NULL);
	expand_variables(&str, envp);
	s2 = split_and_copy(str);
	free(str);
	if (!s2)
		return (NULL);
	remove_quotes2(s2);
	result = check_for_ambiguity(s2);
	return (result);
}

void	ft_expand_red(t_mini *data, t_env *envp)
{
	t_red	*red;

	red = data->red;
	while (red)
	{
		if (red->who == INPUT_RD)
			red->input = ft_expand_red_cr7(red->input, envp);
		if (red->who == RD_TRNC || red->who == RD_APND)
			red->out = ft_expand_red_cr7(red->out, envp);
		if ((red->who == INPUT_RD && !red->input) || ((red->who == RD_TRNC
					|| red->who == RD_APND) && !red->out))
		{
			ft_putendl_fd("Minishell: ambiguous redirect", 2);
		}
		red = red->next;
	}
}
