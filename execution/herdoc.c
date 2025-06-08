/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:46 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/17 17:09:09 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_variables2(char **command, t_env *envp)
{
	int		tab[2];
	char	*tmp;

	tab[0] = 0;
	while ((*command) && (*command)[tab[0]])
	{
		if ((*command)[tab[0]] == '$' && is_valid_key(&(*command)[tab[0] + 1])
			&& (*command)[tab[0] + 1] != '?')
		{
			tab[1] = tab[0] + 1;
			while ((*command)[tab[1]] && ft_isalnum((*command)[tab[1]]))
				tab[1]++;
			tmp = ft_substr((*command), tab[0] + 1, tab[1] - (tab[0] + 1));
			if (tmp && tmp[0])
				tab[0] = handle_j(&(*command), tab, tmp, envp);
			free(tmp);
		}
		else
			hanle_status(&(*command), envp, tab[0]);
		tab[0]++;
	}
}

void	ft_expand_here_doc(char **line, char *limiter, t_env *envp)
{
	if (ft_strchr(limiter, '"') || ft_strchr(limiter, '\''))
		return ;
	expand_variables2(line, envp);
}

void	herdoc_child(t_red *redir, t_env *hold, char *str, int fd)
{
	char	*line;

	signal(SIGINT, x);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			write(2, "warning: here-doc delimited by end-of-file\n", 44);
			break ;
		}
		if (ft_strcmp(line, str) == 0)
		{
			free(line);
			break ;
		}
		ft_expand_here_doc(&line, redir->limiter, hold);
		ft_putendl_fd(line, fd);
		free(line);
	}
	return ;
}

int	herdoc_loop(t_red *redir, t_env *hold)
{
	char	*temp_filename;
	int		fd;
	char	*str;
	int		pid;

	str = rm_qoutes(redir->limiter);
	temp_filename = random_filename();
	fd = open(temp_filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		herdoc_child(redir, hold, str, fd);
		exit(0);
	}
	waitpid(pid, &hold->exit_status, 0);
	hold->exit_status = WEXITSTATUS(hold->exit_status);
	close(fd);
	if (!hold->exit_status)
	{
		redir->who = INPUT_RD;
		redir->input = ft_strdup(temp_filename);
	}
	return (free(temp_filename), free(str), 0);
}

int	handle_herdoc(t_mini *data, t_env *hold)
{
	t_mini	*head;
	t_red	*redir;

	(void)hold;
	head = data;
	while (head)
	{
		redir = head->red;
		while (redir)
		{
			if (redir->who == HERE_DOC)
			{
				herdoc_loop(redir, hold);
				if (hold->exit_status)
					return (hold->exit_status);
			}
			redir = redir->next;
		}
		head = head->next;
	}
	return (0);
}
