/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molatrac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:19:41 by saderdou          #+#    #+#             */
/*   Updated: 2024/09/21 14:36:03 by molatrac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define S_QUOTES -1
# define D_QUOTES -2
# define SPACES -3
# define IN_RED -4
# define OUT_RED -5

//redirection
# define RD_TRNC 1  
# define RD_APND 2 
# define HERE_DOC 3 
# define INPUT_RD 4

//env
# define TEMP_PATH "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

//global
typedef struct s_sig
{
	unsigned char	status;
	char			*prog_name;
}	t_sig;

extern t_sig	*g_status;

//stuct_red_in_out
typedef struct s_red
{
	char				*input;
	char				*out;
	char				*limiter;
	int					who;
	struct s_red		*next;
}	t_red;

typedef struct s_env
{
	t_list			*export_list;
	t_list			*env_list;
	char			**env_arr;
	int				**pipes;
	int				count;
	char			*pwd;
	int				exit_status;
}	t_env;

typedef struct s_mini
{
	char			**command;
	int				type;
	t_red			*red;
	int				idx_pipe;
	struct s_mini	*next;
}	t_mini;

//parsing_fonctions
void	free_list(t_mini *data);
void	free_env(t_env *envp);
t_mini	*ft_parsing(char *str, t_env *hold);
void	ft_error(char *str);
char	**ft_split_pipe(char *str, t_env *hold);
void	ft_free(char **str);
int		ft_error_pipe(char *s);
int		ft_error_red(char **tokens);
char	*ft_space_and_pipes(char *str, t_env *hold);
int		syntax_error(char *read_line);
void	get_new(char *s, char *new);
int		redirection_errors(char *str);
int		ft_strcmp(char *s1, char *s2);

//list
int		get_list_and_cmds(t_mini *input, char *splited);
int		input_or_output_valide(char *splited, int i);
void	ft_cpy(char *splited, int *i, char *str, int *x);
int		get_the_cmd(t_mini *input, char *splited, int len, int i);
int		get_input_and_output_file(t_mini *input, char *splited, int who, int i);
int		input_redirection_and_her_doc(t_mini *input, char *splited, int i);
int		output_redirection_and_append(t_mini *input, char *splited, int i);
int		get_list_and_cmds(t_mini *input, char *splited);
int		get_file_name_or_limiter(char *str, t_red *new_list, int who);
int		input_or_output_valide(char *splited, int i);
int		input_redirection_or_her_doc(t_red *list, char *str, int len, int who);
int		output_and_append_redirection(t_red *list, char *str, int len, int who);
int		lstsize(t_red *lst);
t_red	*lstlast(t_red *lst);
void	lstadd_back(t_red **lscat, t_red *new_node);
t_mini	*lst_last(t_mini *head);
void	lstadd__back(t_mini **input, t_mini *new_node);
void	free_splited(char **splited);
int		quotes_cases_1(char **splited);
void	case_of_single_quotes(char *splited, int *x);
void	case_of_double_quotes(char *splited, int *x);

//pipes_help
int		**create_pipes(int number);
int		ft_count_pipes(t_mini *data);
void	close_unused_pipes(int **pipes, int w_fd, int r_fd);
void	close_and_free_pipes(int **fds);
void	safe_close(int fd);

//execution_fonctions
int		ft_execution(t_mini *data, t_env *hold);
int		ft_count_pipes(t_mini *data);
int		exec_loop(t_mini *data, t_env *hold, int count);
char	*find_path(t_mini *data, t_env *hold);
int		handle_herdoc(t_mini *data, t_env *hold);
int		herdoc_exist(t_mini *data);
int		redirecte(t_red *red);
char	**get_arr(t_list *env);
int		exit_errors(char *cmd_path);
void	pt(char *str);
char	*rm_qoutes(char *str);
char	*random_filename(void);

//builtin_fonctions
int		check_builtin(t_mini *data);
int		exec_builtin(t_mini *data, t_env *envp, int w_fd, int r_fd);
int		ft_pwd(t_mini *data, t_env *envp, int w_fd, int r_fd);
int		ft_cd(t_mini *data, t_env *envp);
void	ft_echo(t_mini *data, t_env *envp, int w_fd, int r_fd);
void	ft_env(t_mini *data, t_env *envp, int w_fd, int r_fd);
int		ft_exit(t_mini *data, t_env *envp);
void	ft_unset(t_mini *data, t_env *envp);
int		ft_export(t_mini *data, t_env *envp, int w_fd);
char	*get_pwd(t_list *env, char *str, int plus);
void	update_help(char **ptr, char *temp);

//signals && main_help
void	x(int c);
void	shell_signals(void);
void	new_line(int signal);
void	quit_coredump(int signal);
void	new_prompt(int signal);
void	init_env(t_env *envp, char **env);
void	update_shlvl(t_list *envp);
void	update_shlvl_export(t_list *export, t_list *envp);

//export_helpe
char	*remove_sum(char *str);
char	*remove_quotes(char *str);
char	*get_var_name(char *str);
void	remove_old_var(t_list **list, char *var_name);
int		get_sum(char *str);
int		is_valid2(char *str);
t_list	*update_value(t_list *lst, char *str, int k, int i);
t_list	*check_sum(char *str, t_list *lst);
char	*ft_strcat(char *dest, char *src);
void	ft_only_export(t_list *export_list, int w_fd);
void	ft_sorting(t_list *list);

//expand
char	**ft_split2(char const *s, char c);
void	ft_expand(t_mini *data, t_env *envp);
void	ft_expand_red(t_mini *data, t_env *envp);
char	*mssa7(char *str);
char	*l_qoutes(char *str, int c);
void	define_flag(char c, int *flag);
int		do_it(char **command, int j, int k, char *value);
char	*check_it(char *str, t_list *lst);
char	**new_arr(char **s2, char *str);
void	expand_variables(char **command, t_env *envp);
int		handle_j(char **command, int *tab, char *tmp, t_env *envp);
char	**split_commands(char **commands);
void	remove_quotes2(char **commands);
int		is_valid_key(char *key);
void	hanle_status(char **s, t_env *envp, int index);
char	**ft_split2(char const *s, char c);
int		isnt(char const *s, int index);

#endif