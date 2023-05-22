/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:18:00 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/19 13:56:43 by lletourn         ###   ########.fr       */
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
Creates a new environment variable by adding it at the end of env.
*/
static void	create_env_var(char *name, char *val, t_list *env)
{
	char	*line;
	t_list	*entry;

	if (!env || !name)
		return ;
	line = ft_strjoin(name, "=");
	free(name);
	line = ft_strjoin_free(line, val);
	entry = ft_lstnew(line);
	ft_lstadd_back(&env, entry);
}

/*
Overwrites an existing environment variable.
*/
static void	overwrite_env_var(char *name, char *val, t_list *env)
{
	char	*prefix;
	int		length;

	if (!env || !name)
		return ;
	prefix = ft_strjoin(name, "=");
	length = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->line, name, length) && env->line[length] == '=')
			break ;
		env = env->next;
	}
	free(env->line);
	env->line = ft_strjoin(prefix, val);
	free(prefix);
}

void	set_env_var(char *name, char *val, t_list *env)
{
	char	*prev_val;

	prev_val = get_var_value(name, env);
	if (!prev_val)
		create_env_var(name, val, env);
	else
		overwrite_env_var(name, val, env);
}
