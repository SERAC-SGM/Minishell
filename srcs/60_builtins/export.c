/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:03:56 by matnam            #+#    #+#             */
/*   Updated: 2023/06/30 16:39:19 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Searches for a character in a string.
Returns 1 if character is found, 0 otherwise.
*/
static int	find_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

/*
Extracts and returns the name from the variable (with malloc).
*/
static char	*get_name(char *var)
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

/*
Extracts and returns the value from the variable (with malloc).
Returns NULL if there is no value.
*/
static char	*get_value(char *var)
{
	char	*value;
	char	*value_tmp;
	size_t	length;

	if (!var)
		return (NULL);
	if (!find_char(var, '='))
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
static int	error_var_name(char *name)
{
	int		i;

	if (!name)
		return (0);
	if (ft_isdigit(name[0]))
		return (error_msg_cmd(E_INVALID_ID, "export: `", name), 1);
	i = 0;
	while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
		i++;
	if (name[i] != 0)
		return (error_msg_cmd(E_INVALID_ID, "export: `", name), 1);
	return (0);
}

/*
Builtin export function.
*/
int	ft_export(char	**args, t_data *data)
{
	char	*name;
	char	*value;
	int		i;

	if (!args || !args[1])
		return (ft_env(data->env, NULL), 0);
	i = -1;
	while (args[++i])
	{
		if (!args[i][0])
			return (error_msg_cmd(E_INVALID_ID, "export: `", "'"), 1);
		name = get_name(args[i]);
		if (error_var_name(name))
			return (free(name), 1);
		else
		{
			value = get_value(args[i]);
			if (value)
				set_env_var(name, value, data, 1);
			else
				free(name);
		}
	}
	return (0);
}
