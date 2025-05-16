/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:00:58 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/15 17:29:52 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static int	ft_output(t_redirect *redirect, int *status)
{
	int		fd;
	char	*file_name;

	file_name = redirect->expanded_file_name;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = err_msg_redirect(file_name);
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = EXIT_SUCCESS;
	return (*status);
}

static int	ft_input(t_redirect *redirect, int *status)
{
	(void)redirect;
	(void)status;
	return (0);
}

static int	ft_append(t_redirect *redirect, int *status)
{
	(void)redirect;
	(void)status;
	return (0);
}

static int	ft_heredoc(t_redirect *redirect, int *status)
{
	(void)redirect;
	(void)status;
	return (0);
}

int	exec_redirect(t_abs_node *node)
{
	t_list			*list;
	t_redirect		*redirect;
	int				status;

	list = node->redirect_list;
	while (list)
	{
		redirect = list->content;
		if (redirect->type == RE_OP_OUTPUT
			&& ft_output(redirect, &status) != EXIT_S_SUCCESS) // >
			return (status);
		else if (redirect->type == RE_OP_INPUT
			&& ft_input(redirect, &status) != EXIT_S_SUCCESS) // <
			return (status);
		else if (redirect->type == RE_OP_APPEND
			&& ft_append(redirect, &status) != EXIT_S_SUCCESS) // >>
			return (status);
		else if (redirect->type == RE_OP_HEREDOC
			&& ft_heredoc(redirect, &status) != EXIT_S_SUCCESS) // <<
			return (status);
		list = list->next;
	}
	return (EXIT_S_SUCCESS);
}


