/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:24:07 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 14:55:31 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "mshell_types.h"

void	exit_error(int err_id, char *item, t_data *data);

#endif
