/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_lib_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:39:34 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/04 15:45:28 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	err_msg_malloc(void)
{
	perror(ERROR_MALLOC);
	return (EXIT_S_FAILURE);
}

int	err_msg_execve(void)
{
	perror(ERROR_EXECVE);
	return (EXIT_S_FAILURE);
}

int	err_msg_getcwd(void)
{
	perror(ERROR_GETCWD);
	return (EXIT_S_FAILURE);
}

int err_msg_fork(void)
{

}