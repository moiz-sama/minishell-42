/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:51:54 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/15 18:00:25 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_mini *data, t_env *envp, int w_fd, int r_fd)
{
	char	*pwd;

	(void)r_fd;
	(void)data;
	(void)envp;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		if (ft_strncmp(envp->pwd, "\0", 1) == 0)
		{
			ft_putendl_fd("getcwd: cannot access parent directories", w_fd);
			return (1);
		}
		write(w_fd, envp->pwd, ft_strlen(envp->pwd));
		write(w_fd, "\n", 1);
		return (0);
	}
	write(w_fd, pwd, ft_strlen(pwd));
	write(w_fd, "\n", 1);
	free(pwd);
	return (0);
}
