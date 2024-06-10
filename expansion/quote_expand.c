/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:16:14 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/10 17:14:01 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*no_quote(char *cmd, int *idx, char *words_tmp)
{
	int	i;
	char	*tmp;
	char	*result;
	int	start;
	int	end;

	i = 0;
	start = *idx;
	while (!(cmd[start + i] == '\'' || cmd[start + i] == '\"' || \
					cmd[start + i] == '\0'))
		i++;
	end = start + i - 1;
	tmp = env_strcpy(start, end, cmd);
	result = ms_strjoin(words_tmp, tmp);
	*idx = end + 1;
	free(tmp);
	if (words_tmp != NULL)
		free(words_tmp);
	return (result);
}

char	*de_quote(char *cmd, int *idx, char *words_tmp, char quote)
{
	int		i;
	int		quote_start;
	int		quote_close;
	char	*in_quote;
	char	*result;

	i = 1;
	quote_start = *idx;
	while (cmd[quote_start + i] != quote)
		i++;
	quote_close = quote_start + i;
	in_quote = env_strcpy(quote_start + 1, quote_close - 1, cmd);
	result = ms_strjoin(words_tmp, in_quote);
	*idx = quote_close + 1;
	free(in_quote);
	if (words_tmp != NULL)
		free(words_tmp);
	return (result);
}

void	handle_quote(t_new_cmd *list, t_env *env)
{
	int		i;
	int		j;
	char	*words_tmp;

	while (list != NULL)
	{
		words_tmp = NULL;
		i = 0;
		while (list->cmd[i] != '\0')
		{
			if (list->cmd[i] == '\'' || list->cmd[i] == '\"')
				words_tmp = de_quote(list->cmd, &i, words_tmp, list->cmd[i]);
			else
				words_tmp = no_quote(list->cmd, &i, words_tmp);
		}
		free(list->cmd);
		// printf("word tmp ::%s\n", words_tmp);
		list->cmd = words_tmp;
		list = list->next;
	}
}


