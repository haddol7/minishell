/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:53:29 by jungslee          #+#    #+#             */
/*   Updated: 2024/06/05 20:05:19 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	handle_error(char *str, int code, t_token **head)
{
	write(2, str, ft_strlen(str));
	if (code == 1)
		exit(1);
	else
	{
		ms_free_all_token(head);
		return (0);
	}
}

t_token	*ms_lstnew(char *value, t_token_type type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		handle_error("exit : malloc error9", 1, 0);
	node->type = type;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_token	*ms_lstlast(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (head == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ms_lstadd_back(t_token **head, t_token *new)
{
	t_token	*last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = ms_lstlast(*head);
		last->next = new;
	}
}

int	ms_free_all_token(t_token **head)
{
	t_token	*to_free;
	t_token	*tmp;

	to_free = *head;
	while (to_free != NULL)
	{
		tmp = to_free->next;
		if (to_free->type != T_EOF)
			free(to_free->value);
		free(to_free);
		to_free = tmp;
	}
	return (0);
}
