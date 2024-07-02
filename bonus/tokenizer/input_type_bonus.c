/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:48:15 by jungslee          #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_bonus.h"

void	eof_node(t_token **head)
{
	t_token	*node;

	node = ms_lstnew(NULL, T_EOF);
	ms_lstadd_back(head, node);
}

int	input_quotation(t_token **head, char *input, int *idx)
{
	int		len;
	int		start;
	char	quote_type;
	char	*value;
	t_token	*node;

	len = 1;
	start = *idx;
	quote_type = input[start];
	while (input[start + len] != quote_type)
	{
		if (input[start + len++] == '\0')
			return (handle_error(ERR_TOK, 0, head));
	}
	while (!(input[start + len] == ' ' || input[start + len] == '\0'))
		len++;
	value = (char *)ft_malloc(sizeof(char) * (len + 2));
	ft_strlcpy(value, (const char *)(input + start), len + 2);
	node = ms_lstnew(value, T_WORD);
	ms_lstadd_back(head, node);
	*idx = start + len;
	return (1);
}

void	input_pipe(t_token **head, int *idx)
{
	char	*value;
	t_token	*node;

	value = ft_strdup("|");
	node = ms_lstnew(value, T_PIPE);
	ms_lstadd_back(head, node);
	*idx = *idx + 1;
}

void	input_redirection(t_token **head, char *input, int *idx)
{
	int				len;
	char			*value;
	t_token_type	type;	
	t_token			*node;

	if (input[*idx] == '<' && input[*idx + 1] == '<')
		type = T_DLESS;
	else if (input[*idx] == '<')
		type = T_LESS;
	else if (input[*idx] == '>' && input[*idx + 1] == '>')
		type = T_DGREAT;
	else
		type = T_GREAT;
	if (input[*idx] == input[*idx + 1])
		len = 2;
	else
		len = 1;
	value = (char *)ft_malloc(sizeof(char) * len + 1);
	ft_strlcpy(value, input + (*idx), len + 1);
	node = ms_lstnew(value, type);
	ms_lstadd_back(head, node);
	*idx = *idx + len;
}
