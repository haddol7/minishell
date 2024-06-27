/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:16:00 by daeha             #+#    #+#             */
/*   Updated: 2024/06/26 16:24:56 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

extern int	g_signal;

void	show_new_prompt(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_status(1);
}

void	kill_child(int signal)
{
	g_signal = signal;
}

void	exit_heredoc(int signal)
{
	(void) signal;
	ft_putendl_fd("", STDOUT_FILENO);
	exit(128 + signal);
}
