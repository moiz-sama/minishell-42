/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:41:52 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/11 09:42:00 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize(t_red *lst)
{
	int		len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst -> next;
	}
	return (len);
}

t_red	*lstlast(t_red *lst)
{
	while (lst)
	{
		if (!lst -> next)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	lstadd_back(t_red **lst, t_red *new_node)
{
	t_red	*mlst;

	if (lst && new_node)
	{
		if (*lst)
		{
			mlst = lstlast(*lst);
			mlst -> next = new_node;
		}
		else
			*lst = new_node;
	}
}

t_mini	*lst_last(t_mini *head)
{
	while (head)
	{
		if (!head -> next)
			return (head);
		head = head -> next;
	}
	return (head);
}

void	lstadd__back(t_mini **input, t_mini *new_node)
{
	t_mini	*mlst;

	if (input && new_node)
	{
		if (*input)
		{
			mlst = lst_last(*input);
			mlst -> next = new_node;
		}
		else
			*input = new_node;
	}
}
