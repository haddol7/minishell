/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:44:05 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_BONUS_H
# define EXECUTION_BONUS_H

# include <stdio.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include "signals_bonus.h"
# include "parser_bonus.h"
# include "expansion_bonus.h"

# define MAX_PIPE 1024
# define MAX_PID 256

# define READ 0
# define WRITE 1
# define INPUT 0
# define OUTPUT 1

# define ENOCMD 0
# define ENOENT 2
# define EACCES 13
# define EISDIR 21
# define EVALUE 1

# define PROC_EXCEED -1

typedef struct s_stat
{
	struct s_env	*envp;
	int				fd[2];
	int				pid[MAX_PID];
	int				n_pid;
	int				fd_dump[MAX_PIPE];
	int				n_dump;
	int				fd_pipe;
}	t_stat;

//e_execution.c
void	execution(t_node *node, t_stat *stat);

//e_and_of_if.c
void	exec_and_or_if(t_node *node, t_stat *stat);

//e_builtin.c
t_bool	is_builtin(char *arg);
void	exec_builtin(t_node *node, t_stat *stat);

//e_cmd.c
void	exec_cmd(t_node *node, t_stat *stat);

//e_cmd_utils.c
void	error_cmd_exit(char *cmd, int error_type);
t_bool	redirect_to_cmd(t_stat *stat, t_bool is_forked);
void	close_dump_fds(t_stat *stat);
void	if_not_executable_then_exit(char *file, char *cmd);
char	*change_as_absolute_path(char *cmd);

//e_pipe.c
void	exec_pipe(t_node *node, t_stat *stat);
void	push_pipe_list(int fd, t_stat *stat);

//e_redir.c
void	exec_redir(t_node *node, t_stat *stat);

//e_redir_here_doc.c
void	exec_here_doc(t_node *node, t_env *envp);

//e_redir_utils.c
void	error_redir(char *name);
int		input(char *filename);
int		append(char *filename);
int		output(char *filename);
int		heredoc(char *filename);

//e_subshell.c
void	exec_subshell(t_node *node, t_stat *stat);

//e_utils.c
void	push_pid_list(pid_t pid, t_stat *stat);
void	wait_pid_list(t_stat *stat);

#endif
