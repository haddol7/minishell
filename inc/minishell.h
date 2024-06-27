/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:26:02 by daeha             #+#    #+#             */
/*   Updated: 2024/06/26 22:44:23 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "parser.h"
# include "expansion.h"
# include "tokenizer.h"
# include "builtin.h"
# include "execution.h"
# include "signals.h"

typedef struct s_minishell
{
	t_node	*ast;
	t_token	*token;
	t_stat	stat;
}	t_minishell;

void	free_all_nodes(t_minishell *ms);
void	save_status(int *pre_status);
void	execution_no_sig(t_node *node, t_stat *stat);
void	add_history_if_not_null(char *input);
int		*get_status(void);
void	set_status(int status);
char	*expand_dollar_here_doc(char *str, struct s_env *envp);

#endif
