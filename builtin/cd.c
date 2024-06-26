/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:32:23 by daeha             #+#    #+#             */
/*   Updated: 2024/06/26 13:17:44 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expansion.h"
#include "execution.h"
#include "minishell.h"

static int	error_enoent(char *arg, char *target, t_bool target_malloc);
static char	*get_absolute_path(char *arg, t_bool *malloc);
static int	home_err(void);

int	ms_cd(char **arg, t_env *env)
{
	t_bool	target_malloc;
	char	*target;
	char	*file;
	char	*old_pwd;

	file = arg[1];
	target_malloc = FALSE;
	if (!file || !ft_strcmp(file, "~"))
	{
		target = env_find_value("HOME", env);
		if (target == NULL)
			return (home_err());
	}
	else if (*file != '.' && *file != '/')
		target = get_absolute_path(file, &target_malloc);
	else
		target = file;
	if (chdir(target) == -1)
		return (error_enoent(file, target, target_malloc));
	if (target_malloc)
		free(target);
	old_pwd = env_update_pwd(&env);
	env_update_oldpwd(&env, old_pwd);
	set_status(EXIT_SUCCESS);
	return (0);
}

static int	error_enoent(char *arg, char *target, t_bool target_malloc)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(2), STDERR_FILENO);
	set_status(EXIT_FAILURE);
	if (target_malloc)
		free(target);
	return (0);
}

static char	*get_absolute_path(char *arg, t_bool *malloc)
{
	char	*target;
	char	*temp;

	target = getcwd(NULL, 0);
	temp = ft_strjoin(target, "/");
	free(target);
	target = ft_strjoin(temp, arg);
	free(temp);
	*malloc = TRUE;
	return (target);
}

static int	home_err(void)
{
	ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
	set_status(EXIT_FAILURE);
	return (0);
}
