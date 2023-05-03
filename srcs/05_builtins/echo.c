/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:57 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/02 14:57:29 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	echo(char **args)
{
	int	newline;
	int	i;

	newline = 1;
	if (!args[1])
		return (0);
	i = -1;
	while (args[++i]
		&& ft_strlen(args[i]) == ft_strlen("-n")
		&& !ft_strncmp("-n", args[i], ft_strlen("-n")))
		newline = 0;
	while (args[i])
		ft_putstr(args[i++]);
	if (newline)
		ft_putstr("\n");
	return (0);
}
