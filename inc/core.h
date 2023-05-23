/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 14:48:27 by matnam            #+#    #+#             */
/*   Updated: 2023/05/23 14:04:04 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "mshell_types.h"

		/////////////
		// 01_init //
		/////////////

/*
Initializes a environment list.
*/
void	init_env(t_data *data, char *env[]);
/*
Initializes a command structure.
*/
void	init_cmd(t_cmd *cmd);
/*
Initializes a data structure.
*/
void	init_data(t_data *data, char *env[]);
/*
Resets data structure to receive new command input :
Frees all allocated memory related to command input.
Keeps environment variables.
*/
void	reset_data(t_data *data);

		////////////
		// 02_env //
		////////////

/*
Returns the value of 'name' stored in a t_list.
Returns NULL if the variable is not found.
*/
char	*get_var_value(char *name, t_list *env);
/*
Sets environment variable by:
• Creating a new line at the end of env if var doesn't exist
• Overwriting an existing line if var_name exist 
*/
void	set_env_var(char *name, char *val, t_list *env);

		///////////////
		// 03_prompt //
		///////////////

char	*prompt(void); //USELESS

		////////////////
		// 04_signals //
		////////////////

	//signal_actions.c

/*
Handles SIGINT signal.
If there is a child process running, handle the interruption and sets an error
status.
If there is no child process, exits the program.
*/
void	sig_int(void);
/*
Handles SIGQUIT singal by displaying a message and setting an error status.
*/
void	sig_quit(void);

	//signal.c
// t_sig	init_sig(void);

void	handler(int signo);
/*
Updates signal handlers for the SIGINT and SIGQUIT signals in childs processes.
*/
void	update_signal(void);
/*
Sets up signal handlers for the SINGINT and SIGQUIT signals
*/
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

/*
Creates a new t_list node.
*/
t_list	*ft_lstnew(void *content);
/*
Returns the last t_list node.
*/
t_list	*ft_lstlast(t_list *lst);
/*
Returns the number of t_list nodes.
*/
int		ft_lstsize(t_list *lst);

	//list_ft2.c

/*
Adds a new node at the end of the list.
*/
void	ft_lstadd_back(t_list **lst, t_list *nnew);
/*
Removes one element of the list.
*/
void	ft_lstdelone(t_list *lst);
/*
Removes all elements of the list.
*/
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
