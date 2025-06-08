/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <molatrac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 19:26:46 by molatrac          #+#    #+#             */
/*   Updated: 2024/08/11 16:00:54 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	head = *lst;
	if (lst && new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		*lst = ft_lstlast(*lst);
		(*lst)->next = new;
		(*lst) = head;
	}
}
