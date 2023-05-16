/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:32:02 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 18:32:19 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_var(char *var, t_list **env)
{
	t_list	*curr;
	t_list	*next;
	int		l;

	l = ft_strlen(var);
	if (!*env)
		return ;
	if (!ft_strncmp((*env)->line, var, l) && (*env)->line[l] == '=')
		return (next = (*env)->next, ft_lstdelone(*env), *env = next, (void)0);
	curr = *env;
	while (curr && curr->next)
	{
		if (!ft_strncmp(curr->next->line, var, l)
			&& curr->next->line[l] == '=')
		{
			next = curr->next->next;
			ft_lstdelone(curr->next);
			curr->next = next;
			return ;
		}
		curr = curr->next;
	}
}

int	unset(char **attr, t_data *data)
{
	int		i;

	i = 1;
	while (attr[i])
	{
		if (get_var_value(attr[i], data->env))
			delete_var(attr[i], &data->env);
		if (get_var_value(attr[i], data->set))
			delete_var(attr[i], &data->set);
		i++;
	}
	return (0);
}
