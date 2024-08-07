/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:04:44 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"
#include "expansion_bonus.h"
#include "minishell_bonus.h"

void	push_pid_list(pid_t pid, t_stat *stat)
{
	stat->pid[stat->n_pid++] = pid;
	if (stat->n_pid == MAX_PID)
	{	
		ft_putendl_fd("minishell : maximum number of process exceeded", \
					STDERR_FILENO);
		wait_pid_list(stat);
		stat->n_pid = PROC_EXCEED;
		set_status(EXIT_FAILURE);
		return ;
	}
}

void	wait_pid_list(t_stat *stat)
{	
	int	pid;
	int	*status;

	pid = 0;
	status = get_status();
	if (stat->n_pid == 0)
		return ;
	while (pid < stat->n_pid)
	{
		waitpid(stat->pid[pid], status, 0);
		pid++;
	}
	stat->n_pid = 0;
	if (WIFEXITED(*status))
		set_status(WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
	{
		set_status(WTERMSIG(*status) + 128);
		if (*status == 131)
			write(1, "Quit: 3", 7);
		write(1, "\n", 1);
	}
}

char	*expand_dollar_here_doc(char *str, t_env *envp)
{
	char	*new_str;
	char	*word_tmp;
	int		i;

	i = 0;
	word_tmp = NULL;
	if (str == NULL)
		return (ft_strdup(""));
	new_str = ft_strdup(str);
	while (new_str[i] != '\0')
	{
		if (new_str[i] == '$')
		{
			word_tmp = return_value(new_str + i, envp);
			if (word_tmp != NULL)
				new_str = replace_cmd(new_str, &word_tmp, &i);
		}
		i++;
	}
	free(str);
	return (new_str);
}

void	del_here_doc_tmp_file(t_node *node)
{
	if (node == NULL || node->type == N_CMD)
		return ;
	if (node->type == N_HERE_DOC)
		unlink(node->right->cmd[0]);
	del_here_doc_tmp_file(node->left);
	del_here_doc_tmp_file(node->right);
}
