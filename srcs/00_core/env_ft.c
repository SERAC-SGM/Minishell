/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:18:00 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 14:44:05 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *name, t_list *env)
{
	int		l;
	
	if (!env || !name)
		return (NULL);
	l = ft_strlen(name);
	while (env)
	{
		if (!ft_strncmp(env->line, name, l) && env->line[l] == '=')
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (ft_strchr(env->line, '=') + 1);
}

static void	create_env_var(char *name, char *val, t_list *env)
{
	char	*line;
	t_list	*entry;

	if (!env || !name)
		return (NULL);
	line = ft_strjoin(name, "=");
	line = ft_strjoin_free(line, val);
	entry = ft_lstnew(line);
	ft_lstadd_back(&env, entry);
}

static void	overwrite_env_var(char *name, char *val, t_list *env)
{
	char	*prefix;

	if (!env || !name)
		return (NULL);
	prefix = ft_strjoin(name, "=");
	while (env)
	{
		if (!ft_strncmp(env->line, name, l) && env->line[l] == '=')
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

	prev_val = get_var_value(name, data->env);
	if (!prev_val)
		create_env_var(name, val, data);
	else
		overwrite_env_var(name, val, data);
}

