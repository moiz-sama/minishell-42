/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saderdou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:18:15 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/17 18:40:15 by saderdou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	*g_status;

int	to_be_continued(t_mini *data, t_env *envp)
{
	char	*str;

	while (1)
	{
		shell_signals();
		str = readline("minishell > ");
		if (g_status->status != 0)
		{
			envp->exit_status = g_status->status;
			g_status->status = 0;
		}
		if (!str)
			return (write(1, "exit\n", 5), 0);
		data = ft_parsing(str, envp);
		if (data != NULL)
		{
			add_history(str);
			envp->exit_status = ft_execution(data, envp);
			free_list(data);
		}
		free(str);
	}
	return (envp->exit_status);
}

int	main(int ac, char **av, char **env)
{
	t_mini	*data;
	t_env	*envp;
	t_sig	sig;
	int		exit_status;

	data = NULL;
	exit_status = 0;
	envp = malloc(sizeof(t_env));
	if (ac != 1)
		return (ft_error("ac > 1"), 0);
	init_env(envp, env);
	update_shlvl(envp->env_list);
	update_shlvl_export(envp->export_list, envp->env_list);
	sig.prog_name = av[0];
	sig.status = 0;
	g_status = &sig;
	envp->exit_status = 0;
	exit_status = to_be_continued(data, envp);
	rl_clear_history();
	free(envp->pwd);
	free_env(envp);
	return (exit_status);
}
