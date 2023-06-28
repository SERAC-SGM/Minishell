/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/28 14:01:41 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_data *data)
{
	char	*path;
	char	*tail_path;
	char	*prompt;
	char	*tmp;

	path = get_var_value("HOME", data->env);
	prompt = get_var_value("PWD", data->env);
	if (!path && prompt)
		return (ft_strdup(prompt));
	if (!prompt)
		return (ft_strdup (""));
	tmp = ft_strdup(ft_strstr(prompt, path));
	if (!tmp || !tmp[0])
		return (free(tmp), ft_strdup(prompt));
	tail_path = ft_strdup(tmp + ft_strlen(path));
	free(tmp);
	if (!tail_path)
		return (free(tail_path), ft_strdup(prompt));
	tmp = ft_strjoin("~", tail_path);
	free(tail_path);
	return (tmp);
}

static void	display_prompt(t_data *data)
{
	char	*prompt;
	char	*tmp;

	tmp = get_home_path(data);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	data->cmd_line = readline(prompt);
	free(prompt);
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	(void)ac;
	(void)av;
	enable_signal();
	init_data(&data, env);
	while (!g_sig.exit)
	{
		reset_data(&data);
		display_prompt(&data);
		if (!data.cmd_line)
			break ;
		if (*data.cmd_line)
		{
			add_history(data.cmd_line);
			lexer(&data);
			if (parser(&data))
				exec_cmd_line(&data);
			clear_token_list(&data.token_list);
		}
	}
	clear_data(&data);
	write(1, "exit\n", 5);
	return (g_sig.error_status);
}
