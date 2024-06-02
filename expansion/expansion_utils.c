/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungslee <jungslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:46:42 by jungslee          #+#    #+#             */
/*   Updated: 2024/05/31 17:13:58 by jungslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

t_env	*env_new(char *name, char *content)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		handle_error("exit : malloc error", 1, 0);
	node->name = name;
	node->content = content;
	node->next = NULL;
	return (node);
}

t_env	*env_last(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	if (head == NULL)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	env_add_back(t_env **head, t_env *new)
{
	t_env	*last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = env_last(*head);
		last->next = new;
	}
}

int	env_free_all(t_env **head)
{
	t_env	*to_free;
	t_env	*tmp;

	to_free = *head;
	while (to_free != NULL)
	{
		tmp = to_free->next;
		if (to_free->name != NULL)
			free(to_free->name);
		if (to_free->content != NULL)
			free(to_free->content);
		free(to_free);
		to_free = tmp;
	}
	return (0);
}

// void	env_del_one(t_env **head, t_env *node)
// {
// 	t_env *tmp;

// 	tmp = head;
// 	while (head->name)
// }