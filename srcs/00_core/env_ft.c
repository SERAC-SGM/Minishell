/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:18:00 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 14:26:37 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *to_find, t_list *env)
{
	int		l;

	if (!env || !to_find)
		return (NULL);
	l = ft_strlen(to_find);
	while (env)
	{
		if (!ft_strncmp(env->line, to_find, l) && env->line[l] == '=')
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (ft_strchr(env->line, '=') + 1);
}

void	set_env_var(char *name, char *value, t_data *data)
{

}

void	overwrite_env_var(char *name, char *value, t_data *data)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_shell->env[i])
	{
		if (!ft_strncmp(g_shell->env[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	free(g_shell->env[i]);
	g_shell->env[i] = ft_strjoin(aux, value);
	free_three_ptrs(name, value, aux);
}

void	add_to_env(char *name, char *value, t_data *data)
{
	char	*prev_value;

	prev_value = check_env(name);
	if (!prev_value)
		add_to_local_env(name, value);
	else
	{
		free(prev_value);
		overwrite_env_value(name, value);
	}
}
