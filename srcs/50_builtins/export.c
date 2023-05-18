/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:03:56 by matnam            #+#    #+#             */
/*   Updated: 2023/05/18 16:46:50 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

*/
static char	*set_var_name(char *var)
{
	char	*name;
	size_t	length;

	if (!var)
		return (NULL);
	length = ft_abs(ft_strchr(var, '=') - var + 1);
	if (!length)
		return (var);
	name = malloc(sizeof(char) * (length + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, var, length);
	return (name);
}

static char	*set_var_value(char *var)
{
	char	*value;
	char	*value_tmp;
	size_t	length;

	if (!var)
		return (NULL);
	value_tmp = ft_strchr(var, '=') + 1;
	length = ft_abs(ft_strlen(value_tmp) + 1);
	if (!length)
		return (NULL);
	value = malloc(sizeof(char) * (length + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, value_tmp, length);
	return (value);
}


/*
Checks if the variable is assigned in set, and exports it. If it's unnasigned,
does nothing.
*/
static void	export_unassigned(char *name, t_list *env, t_list *set)
{
	char	*value;

	value = get_var_value(name, set);
	if (!value)
		return ;
	set_env_var(name, value, env);
}

void	ft_export(char	**args, t_list *env, t_list *set)
{
	char	*name;
	char	*value;

	while (args++)
	{
		if (!*args)
			return ;
		name = set_var_name(*args);
		value = set_var_value(*args);
		if (!value)
			export_unassigned(name, env, set);
		else
			set_env_var(name, value, env);
	}
}
