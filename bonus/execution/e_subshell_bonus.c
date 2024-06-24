/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_subshell_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:07 by daeha             #+#    #+#             */
/*   Updated: 2024/06/25 04:35:09 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"
#include "minishell_bonus.h"

void	exec_subshell(t_node *node, t_stat *stat)
{
	pid_t	pid;
	int		*status;

	status = get_status();
	pid = fork();
	if (!pid)
	{	
		stat->n_pid = 0;
		close_dump_fds(stat);
		execution(node->left, stat);
		wait_pid_list(stat);
		if (stat->fd[INPUT] != STDIN_FILENO)
			close(stat->fd[INPUT]);
		if (stat->fd[OUTPUT] != STDOUT_FILENO)
			close(stat->fd[OUTPUT]);
		status = get_status();
		exit(*status);
	}
	else
	{
		sig_parent_mode();
		push_pid_list(pid, stat);
	}
}
