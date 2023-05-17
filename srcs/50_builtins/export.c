/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:03:56 by matnam            #+#    #+#             */
/*   Updated: 2023/05/17 23:31:08 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_var_name(char *var)
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

char	*set_var_value(char *var)
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

void	export_assign(char *arg, t_list *env, t_list *set)
{
	char	*name;
	char	*value;
	(void)arg;
	(void)env;
	(void)set;
	(void)name;
	(void)value;
}

void	ft_export(char	**args, t_list *env, t_list *set)
{
	char	*name;
	char	*value;

	(void)env;
	(void)set;
	while (args++)
	{
		if (*args)
		{
			name = set_var_name(*args);
			value = set_var_value(*args);
			if (!value)
			{
				if (name)
					return ;			}
		}
	}
}
