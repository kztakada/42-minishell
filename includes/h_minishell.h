/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:56:46 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/04 01:21:47 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINISHELL_H
# define H_MINISHELL_H

// includes
# include "../libraries/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

// prototypes builtins
int		ft_cd(char *path);
int		ft_echo(char **args);
int		ft_env(void);
void	ft_exit(char **args);
int		ft_export(char **argv);
int		ft_pwd(void);
int		ft_unset(char **args);

//prototypes exec
int		ft_exec_builtin(char **args);
int		ft_check_redirection(t_node *node);

#endif