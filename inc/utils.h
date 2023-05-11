/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:32:01 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 15:35:29 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "mshell_types.h"

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *nnew);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);
void	print_lexer(t_tkn_lst *lex);
void	print_env(t_list *env);
void	trim_char(char **str, char c);
char	*ft_strjoin_dup1(char *s1, char *s2);

#endif