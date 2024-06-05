/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/05 16:33:51 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <fcntl.h>
# include "minishell.h"

# define READ 0
# define INPUT 0
# define WRITE 1
# define OUTPUT 1
# define ERR_REDIR 1

//redirection.c
int	input(char *filename);
int	append(char *filename);
int	heredoc(char *delim);
int	output(char *filename);

//exec_redir.c
void	exec_redir(struct s_node *node, int fd[2]);

#endif