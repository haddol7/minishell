/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:02:12 by daeha             #+#    #+#             */
/*   Updated: 2024/06/17 21:25:23 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"

extern int	g_status;

static void	exec_proc(char **arg, t_stat *stat);
static void	set_arg_path(char **cmd, t_env *envp);
static char	*match_in_env_path(char *cmd, char **path);
static char	*match_in_current_path(char *cmd);

//TODO: signal 작업
void	exec_cmd(t_node *node, t_stat *stat)
{
	pid_t	pid;

	cmd_expansion(node, stat->envp);
	if (node->cmd && is_builtin(node->cmd[0]))
	{
		exec_builtin(node, stat);
		return ;
	}
	pid = fork();
	if (!pid)
		exec_proc(node->cmd, stat);
	else
	{
		push_pid_list(pid, stat);
		if (stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
	}
}

static void	exec_proc(char **arg, t_stat *stat)
{
	close_pipe_fds(stat);
	redirect_to_cmd(stat, TRUE);
	set_arg_path(&arg[0], stat->envp);
	execve(arg[0], arg, env_join(stat->envp));
	exit(EXIT_FAILURE);
}

static void	set_arg_path(char **cmd, t_env *envp)
{
	char	**path;
	char	*file;

	if (ft_strcmp(*cmd, "") && ft_strchr(*cmd, '/') == NULL)
	{
		path = ft_split(env_find_value("PATH", envp), ':');
		file = match_in_env_path(*cmd, path);
		free_double_pointer(path);
	}
	else if (ft_strcmp(*cmd, ""))
		file = match_in_current_path(*cmd);
	else
		file = NULL;
	if_not_executable_then_exit(file, *cmd);
	free(*cmd);
	*cmd = file;
}

static char	*match_in_current_path(char *cmd)
{	
	char	*file;
	char	*current_path;

	if (*cmd == '/')
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	current_path = getcwd(NULL, 0);
	file = change_as_absolute_path(cmd);
	chdir(current_path);
	if (!access(file, F_OK | X_OK))
		return (file);
	free(file);
	return (NULL);
}

static char	*match_in_env_path(char *cmd, char **path)
{
	char	*file;
	char	*cmd_slash;
	char	*cur_path;

	cmd_slash = ft_strjoin("/", cmd);
	while (path && *path != NULL)
	{	
		file = ft_strjoin(*path, cmd_slash);
		if (!access(file, F_OK | X_OK))
		{
			free(cmd_slash);
			return (file);
		}
		free(file);
		path++;
	}
	cur_path = getcwd(NULL, 0);
	file = ft_strjoin(cur_path, cmd_slash);
	free(cmd_slash);
	free(cur_path);
	if (!access(file, F_OK | X_OK))
		return (file);
	free(file);
	error_cmd_exit(cmd, ENOCMD);
	return (NULL);
}
