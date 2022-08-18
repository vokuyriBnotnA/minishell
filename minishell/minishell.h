/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klemongr <klemongr@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:17:24 by klemongr          #+#    #+#             */
/*   Updated: 2022/04/28 10:31:47 by klemongr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/dir.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_variables
{
	char				*name;
	char				*value;
	struct s_variables	*next;

}	t_variables;

typedef struct s_commands
{
	char				*cmd;
	char				**cmd_execve;
	char				*path;
	int					fd_in;
	int					fd_out;
	char				*here_doc_flag;
	int					redir_output_append;
	int					interpret_flag;
	int					my_func;
	struct s_commands	*next;

}	t_commands;

typedef struct s_minishell
{
	t_variables	*var;
	t_variables	*var_current;
	t_commands	*commands;
	t_commands	*commands_current;
	char		*path;
	int			pipe_count;
	char		*cmd;
	int			argc;
	char		**argv;
	char		**envp;
	int			i;
}	t_minishell;

char		*g_exit_code;

t_commands	*init_commands(void);
t_commands	*add_commands(t_commands *lst);
int			history_init(t_minishell *ms);
int			ms_history_add(t_minishell *ms);
int			ms_history_print(t_minishell *ms);
int			read_cmd(t_minishell *ms);
int			variables_init(t_minishell *ms);
int			parsing(t_minishell *ms);
int			parsing_2(t_minishell *ms, char *cmd_to_pipe, int *i, char *quotes);
int			parsing_3(t_minishell *ms, char *cmd_to_pipe);
int			further_process_cmd(t_minishell *ms, char *cmd);
int			redirections(t_minishell *ms, char *cmd, int *count, char type);
int			open_file(t_minishell *ms, char *filename, char type);
int			here_doc(t_minishell *ms);
int			excerpt_cmd(t_minishell *ms, char *cmd, int *count);
int			execution(t_minishell *ms);
int			pipes(t_minishell *ms, int count, int *fd, int *fd_2);
int			is_my_func(char *str);
int			is_my_func_child(char *str);
int			my_func(char *cmd_name, char **cmd, t_minishell *ms);
int			my_func_child(char *cmd_name, char **cmd, t_minishell *ms);
void		unset(t_minishell *ms, char *var_name);
void		exit_ms(char *num);
int			env_ms(t_minishell *ms);
int			export_ms(t_minishell *ms);
int			cd(char *path);
char		*path_func(char *cmd, char **envp);
int			execution_1(t_minishell *ms);
int			execution_2(t_minishell *ms, pid_t **pid);
int			execution_3(t_minishell *ms);
int			execution_pipe(t_minishell *ms, int *fd, int *fd_2, int i);
int			execution_work(t_minishell *ms, int *fd, int *fd_2, pid_t *pid);
int			ft_strlen(char *str);
int			ft_strlen_plus(char *str, char c);
char		**ft_split(char *str, char c);
char		**free_split(char **str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnstr(char *haystack, char *needle, int len);
char		*get_next_line(int fd);
int			compare_str(char *s1, char *s2, int len);
char		*dup_str(char *str);
int			free_ms_var(t_minishell *ms);

#endif