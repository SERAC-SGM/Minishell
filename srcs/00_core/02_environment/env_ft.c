/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:18:00 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/27 16:56:34 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *name, t_list *env)
{
	int	length;

	if (!env || !name)
		return (NULL);
	length = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->line, name, length) && env->line[length] == '=')
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (ft_strchr(env->line, '=') + 1);
}

/*
C'est moche mais ça marche
*/
/*
Creates a new environment variable by adding it at the end of env.
*/
static void	create_env_var(char *name, char *val, t_data *data, int malloc)
{
	char	*line;
	t_list	*entry;

	if (!name)
		return ;
	line = ft_strjoin(name, "=");
	if (malloc)
		free(name);
	if (malloc)
		line = ft_strjoin_free(line, val);
	else
		line = ft_strjoin_dup1(line, val);
	entry = ft_lstnew(line);
	if (!data->env)
		data->env = entry;
	else
		ft_lstadd_back(&data->env, entry);
}

/*
Overwrites an existing environment variable.
*/
static void	overwrite_env_var(char *name, char *val, t_data *data, int malloc)
{
	t_list	*env;
	char	*prefix;
	int		length;

	env = data->env;
	if (!name)
		return ;
	prefix = ft_strjoin(name, "=");
	length = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->line, name, length) && env->line[length] == '=')
			break ;
		env = env->next;
	}
	if (malloc)
		free(name);
	free(env->line);
	if (malloc)
		env->line = ft_strjoin_free(prefix, val);
	else
	{
		env->line = ft_strjoin(prefix, val);
		free(prefix);
	}
}

void	set_env_var(char *name, char *val, t_data *data, int malloc)
{
	char	*prev_val;

	prev_val = get_var_value(name, data->env);
	if (!prev_val)
		create_env_var(name, val, data, malloc);
	else
		overwrite_env_var(name, val, data, malloc);
}
