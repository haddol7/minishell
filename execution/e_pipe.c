/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:03:01 by daeha             #+#    #+#             */
/*   Updated: 2024/06/23 17:33:11 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	push_pipe_list(int fd[2], t_stat *stat);

void	exec_pipe(t_node *node, t_stat *stat)
{
	int	fd[2];
	int	origin[2];

	stat->is_pipe = TRUE;
	origin[INPUT] = stat->fd[INPUT];
	origin[OUTPUT] = stat->fd[OUTPUT];
	pipe(fd);
	stat->fd[OUTPUT] = fd[OUTPUT];
	push_pipe_list(fd, stat);
	//printf("left-pipe - %d %d \n", stat->fd[INPUT], stat->fd[OUTPUT]);
	execution(node->left, stat);
	stat->n_pipe--;
	stat->fd[OUTPUT] = origin[OUTPUT];
	stat->fd[INPUT] = fd[INPUT];
	//printf("right-pipe - %d %d \n", stat->fd[INPUT], stat->fd[OUTPUT]);
	execution(node->right, stat);
	stat->n_pipe--;
	stat->fd[INPUT] = origin[INPUT];
	stat->is_pipe = FALSE;
}

static void	push_pipe_list(int fd[2], t_stat *stat)
{
	stat->pipe[stat->n_pipe++] = fd[OUTPUT];
	stat->pipe[stat->n_pipe++] = fd[INPUT];
	if (stat->n_pipe == MAX_PIPE)
	{
		ft_putendl_fd("minishell : maximum number of process exceeded", \
					STDERR_FILENO);
		wait_pid_list(stat);
		ft_putendl_fd("exit...", STDERR_FILENO);
	}
}
