/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:27:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/17 21:14:40 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

extern int	g_status;

static t_bool	is_redir_in(t_node_type type);


//TODO: g_status 삭제
void	exec_redir(t_node *node, t_stat *stat)
{
	char	**filename;
	char	*error_str;
	
	error_str = ft_strdup(node->right->cmd[0]);
	cmd_expansion(node->right, stat->envp);
	filename = node->right->cmd;
	if (filename[0] == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(error_str, STDERR_FILENO);
		ft_putendl_fd(": ambigous redirect", STDERR_FILENO);
		g_status = EXIT_FAILURE;
	}
	if (stat->fd[INPUT] != -1 && stat->fd[OUTPUT] != -1)
	{
		if (stat->fd[INPUT] != STDIN_FILENO && is_redir_in(node->type))
			close(stat->fd[INPUT]);
		else if (stat->fd[OUTPUT] != STDOUT_FILENO && !is_redir_in(node->type))
			close(stat->fd[OUTPUT]);
		if (node->type == N_INPUT)
			stat->fd[INPUT] = input(node->right->cmd[0]);
		else if (node->type == N_HERE_DOC)
			stat->fd[INPUT] = heredoc(node->right->cmd[0]);
		else if (node->type == N_OUTPUT)
			stat->fd[OUTPUT] = output(node->right->cmd[0]);
		else
			stat->fd[OUTPUT] = append(node->right->cmd[0]);
	}
	execution(node->left, stat);
}

static t_bool	is_redir_in(t_node_type type)
{
	if (type == N_INPUT || type == N_HERE_DOC)
		return (TRUE);
	return (FALSE);
}
