/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:56:31 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/25 12:59:10 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*random_filename(void)
{
	unsigned char	filename[8 + 1];
	int				fd;
	int				i;
	int				r_len;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (NULL);
	r_len = read(fd, filename, 8);
	if (r_len <= 0)
		return (NULL);
	i = 0;
	filename[r_len] = 0;
	while (i < r_len)
	{
		filename[i] = (filename[i] % 25) + 65;
		i++;
	}
	close(fd);
	return (ft_strjoin("/tmp/minishell_heredoc_", (char *)filename));
}

char	*rm_qoutes(char *str)
{
	int		i;
	int		j;
	char	*new;
	int		s_qoutes;
	int		d_qoutes;

	i = 0;
	j = 0;
	s_qoutes = 0;
	d_qoutes = 0;
	new = malloc(strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && !s_qoutes)
			d_qoutes = !d_qoutes;
		else if (str[i] == '\'' && !d_qoutes)
			s_qoutes = !s_qoutes;
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	herdoc_exist(t_mini *data)
{
	t_mini	*head;
	t_red	*red;
	int		i;

	head = data;
	i = 0;
	while (head)
	{
		red = head->red;
		while (red)
		{
			if (red->who == HERE_DOC)
				i++;
			red = red->next;
		}
		head = head->next;
	}
	return (i);
}
