/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:53:38 by molatrac          #+#    #+#             */
/*   Updated: 2024/09/15 17:58:55 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_export(char *str, int w_fd)
{
	int		check;
	char	*original_str;

	check = 0;
	original_str = str;
	write(w_fd, "declare -x ", 12);
	while (str && *str)
	{
		write(w_fd, str, 1);
		if (*str == '=' && check == 0)
		{
			check = -1;
			write(w_fd, "\"", 1);
		}
		str++;
	}
	if (ft_strchr(original_str, '='))
		write(w_fd, "\"", 1);
	write(w_fd, "\n", 2);
}

void	ft_only_export(t_list *export_list, int w_fd)
{
	t_list	*node;
	char	*str;

	node = export_list;
	while (node)
	{
		str = (char *)node->content;
		if (ft_strncmp(str, "_=", 2) != 0
			&& ft_strncmp(str, TEMP_PATH, ft_strlen(TEMP_PATH)) != 0)
			write_export(str, w_fd);
		node = node->next;
	}
}

void	ft_sorting(t_list *list)
{
	int		flag;
	char	*swp;
	t_list	*node;

	flag = 1;
	while (flag)
	{
		flag = 0;
		node = list;
		while (node && node->next)
		{
			if (ft_strncmp(node->content, node->next->content,
					ft_strlen(node->next->content)) > 0)
			{
				swp = node->content;
				node->content = node->next->content;
				node->next->content = swp;
				flag = 1;
			}
			node = node->next;
		}
	}
}
