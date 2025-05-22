/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:00:58 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/22 04:01:50 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static int	redirect_output_to_file(char *file_name, int *status)
{
	int		fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = err_msg_redirection(file_name);
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = EXIT_S_SUCCESS;
	return (*status);
}

static int	redirect_input_from_file(char *file_name, int *status)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		*status = err_msg_redirection(file_name);
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = EXIT_S_SUCCESS;
	return (*status);
}

static int	redirect_append_to_file(char *file_name, int *status)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = err_msg_redirection(file_name);
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = EXIT_S_SUCCESS;
	return (*status);
}

static int	redirect_input_from_fd(int fd, int *status)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = EXIT_S_SUCCESS;
	return (*status);
}

int	exec_redirection(t_abs_node *node)
{
	t_list			*list;
	t_redirection	*redirection;
	char			*file_name;
	int				status;

	list = node->redirection_list;
	while (list)
	{
		redirection = list->content;
		file_name = redirection->expanded_file_name;
		if (redirection->type == RE_OP_OUTPUT
			&& redirect_output_to_file(file_name, &status) != EXIT_S_SUCCESS)
			return (status);
		else if (redirection->type == RE_OP_INPUT
			&& redirect_input_from_file(file_name, &status) != EXIT_S_SUCCESS)
			return (status);
		else if (redirection->type == RE_OP_APPEND
			&& redirect_append_to_file(file_name, &status) != EXIT_S_SUCCESS)
			return (status);
		else if (redirection->type == RE_OP_HEREDOC
			&& redirect_input_from_fd(redirection->fd, &status) != EXIT_S_SUCCESS)
			return (status);
		list = list->next;
	}
	return (EXIT_S_SUCCESS);
}
