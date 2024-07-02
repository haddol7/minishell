/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:46:14 by daeha             #+#    #+#             */
/*   Updated: 2024/07/02 17:38:42 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"
#include "minishell_bonus.h"

static t_bool	is_str_option(char *str, t_bool *option);

void	ms_echo(char **arg)
{
	t_bool	option;

	option = FALSE;
	while (*arg)
	{
		arg++;
		if (!is_str_option(*arg, &option))
			break ;
	}
	while (*arg)
	{
		ft_putstr_fd(*(arg)++, STDOUT_FILENO);
		if (*arg)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	set_status(EXIT_SUCCESS);
}

static t_bool	is_str_option(char *str, t_bool *option)
{
	size_t	i;

	i = 2;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (FALSE);
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	*option = TRUE;
	return (TRUE);
}
