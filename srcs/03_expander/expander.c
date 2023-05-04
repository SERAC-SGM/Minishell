/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 15:50:56 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Expand variable followed by $ in format by the corresponding value in env
• $ is not iterpreted when into single quote
*/
t_tkn_lst	*expander(t_tkn_lst *token, t_list *env)
{
	int		i;
	int		idx_l;
	int		var_pos;
	int 	var_len;
	char	*exp;

	var_pos = 0;
	while (token->content[var_pos] && token->content[var_pos] != '$')
		var_pos++;
	var_len = word_len(&token->content[i + 1]);
	idx_l = 0;
	ft_strchr()
	
	free(token->content)
	token->cotent = exp;
	if (!token->content)
		return (0);

}