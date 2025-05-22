/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:58:06 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/22 03:58:49 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static t_err	identify_redirection_error(char *file_name)
{
	struct stat	buf;

	stat(file_name, &buf);
	if (S_ISDIR(buf.st_mode))
		return (create_t_err(EXIT_S_FAILURE, ERRMSG_IS_DIRECTORY, file_name));
	if (access(file_name, F_OK) == 0)
		return (create_t_err(EXIT_S_FAILURE, ERRMSG_PERM_DENIED, file_name));
	else
		return (create_t_err(EXIT_S_FAILURE, ERRMSG_NO_SUCH_FILE, file_name));
}

int	err_msg_redirection(char *filename)
{
	t_err	err;

	err = identify_redirection_error(filename);
	if (err.msg == ERRMSG_PERM_DENIED)
		return (msg_perm_denied(err));
	else if (err.msg == ERRMSG_IS_DIRECTORY)
		return (msg_is_directory(err));
	else if (err.msg == ERRMSG_NO_SUCH_FILE)
		return (msg_no_such_file(err));
	return (EXIT_S_SUCCESS);
}
