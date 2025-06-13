/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_stds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 06:28:06 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/10 01:24:50 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_saved_std	save_stds(void)
{
	t_saved_std	std;

	std.saved_stdin = dup(0);
	std.saved_stdout = dup(1);
	return (std);
}

void	reset_stds(t_saved_std *std, t_bool redirected)
{
	if (redirected == TRUE)
		return ;
	dup2(std->saved_stdin, 0);
	dup2(std->saved_stdout, 1);
	return ;
}
