/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:48:27 by matnam            #+#    #+#             */
/*   Updated: 2023/05/18 13:54:35 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mshell_types.h"

/////////////
// 01_init //
/////////////

void	init_env(t_data *data, char *env[]);
void	init_cmd(t_cmd *cmd);
void	init_data(t_data *data, char *env[]);
void	reset_data(t_data *data);

////////////
// 02_env //
////////////

char	*get_var_value(char *name, t_list *env);
void	set_env_var(char *name, char *val, t_list *env);

///////////////
// 03_prompt //
///////////////

char	*prompt(void);

////////////////
// 04_signals //
////////////////

//signal_actions.c
void	sig_int(void);
void	sig_quit(void);

//signal.c
// t_sig	init_sig(void);
void	handler(int signo);
void	update_signal(void);
void	enable_signal(void);

//////////////
// 05_error //
//////////////

void	error_msg(int err_id, char *item, t_data *data);
void	error_msg_cmd(int err_id, char *prefix, char *item);
void	exit_error(int err_id, char *item, t_data *data);

/////////////
// 06_free //
/////////////
void	clear_data(t_data *data);
void	clear_exit(t_data *data);

//////////////
// 09_utils //
//////////////

//list_ft.c
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
//list_ft2.c
void	ft_lstadd_back(t_list **lst, t_list *nnew);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);
//print_struct.c
void	print_lexer(t_tkn_lst *lex);
void	print_env(t_list *env);
void	print_tab(char **tab);
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_data *data);
//util.c
void	trim_char(char **str, char c);
char	*ft_strjoin_dup1(char *s1, char *s2);
int		tab_size(char **tab);

#endif
