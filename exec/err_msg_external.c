/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:56:37 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/11 17:19:14 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	msg_cmd_not_found(t_err err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err.cause, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (err.exit_s);
}

int	msg_no_such_file(t_err err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err.cause, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (err.exit_s);
}

int	msg_perm_denied(t_err err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err.cause, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	return (err.exit_s);
}

int	msg_is_directory(t_err err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err.cause, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	return (err.exit_s);
}

int	err_msg_external(t_err err)
{
	if (err.msg == ERRMSG_CMD_NOT_FOUND)
		return (msg_cmd_not_found(err));
	else if (err.msg == ERRMSG_NO_SUCH_FILE)
		return (msg_no_such_file(err));
	else if (err.msg == ERRMSG_PERM_DENIED)
		return (msg_perm_denied(err));
	else if (err.msg == ERRMSG_IS_DIRECTORY)
		return (msg_is_directory(err));
	else if (err.msg == ERRMSG_MALLOC)
		return (perror(ERROR_MALLOC), EXIT_S_FAILURE);
	return (EXIT_S_SUCCESS);
}
