/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:22:32 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/23 01:30:40 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_err	create_t_err(int err_exit_s, int err_msg, char *err_cause)
{
	t_err err;

	err.exit_s = err_exit_s;
	err.msg = err_msg;
	err.cause = err_cause;
	return (err);
}

t_path	create_t_path(char *cmd, int err_exit_s,
	int err_msg, char *err_cause)
{
	t_path	path;

	path.path = cmd;
	path.err = create_t_err(err_exit_s, err_msg, err_cause);
	return (path);
}