/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:00:58 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/16 11:53:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static int	ft_output(t_redirection *redirection, int *status)
{
	int		fd;
	char	*file_name;

	file_name = redirection->expanded_file_name;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = err_msg_redirection(file_name);
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = EXIT_SUCCESS;
	return (*status);
}

static int	ft_input(t_redirection *redirection, int *status)
{
	(void)redirection;
	(void)status;
	return (0);
}

static int	ft_append(t_redirection *redirection, int *status)
{
	(void)redirection;
	(void)status;
	return (0);
}

static int	ft_heredoc(t_redirection *redirection, int *status)
{
	(void)redirection;
	(void)status;
	return (0);
}

int	exec_redirection(t_abs_node *node)
{
	t_list			*list;
	t_redirection		*redirection;
	int				status;

	list = node->redirection_list;
	while (list)
	{
		redirection = list->content;
		if (redirection->type == RE_OP_OUTPUT
			&& ft_output(redirection, &status) != EXIT_S_SUCCESS) // >
			return (status);
		else if (redirection->type == RE_OP_INPUT
			&& ft_input(redirection, &status) != EXIT_S_SUCCESS) // <
			return (status);
		else if (redirection->type == RE_OP_APPEND
			&& ft_append(redirection, &status) != EXIT_S_SUCCESS) // >>
			return (status);
		else if (redirection->type == RE_OP_HEREDOC
			&& ft_heredoc(redirection, &status) != EXIT_S_SUCCESS) // <<
			return (status);
		list = list->next;
	}
	return (EXIT_S_SUCCESS);
}


