/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:43:00 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/18 15:05:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_garbage_collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}

char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_garbage_collector(
					ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}

void	ft_env_lst_back(t_env *new, t_env *env_lst)
{
	t_env	*curr;

	if (!env_lst)
	{
		env_lst = new;
		return ;
	}
	curr = env_lst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

t_env	*ft_env_lst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_garbage_collector(ft_strdup(key), false);
	if (value)
		new->value = ft_garbage_collector(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

void	ft_update_env_lst(char *key, char *value, bool create, t_env **env_lst)
{
    t_env	*new_node;
    t_env	*current;

    if (!key || !value || !env_lst)
        return;

    current = *env_lst;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }

    if (create)
    {
        new_node = ft_env_lst_new(key, value);
        if (!new_node)
            return;
        new_node->next = *env_lst;
        *env_lst = new_node;
    }
}

t_env *make_env_list(char **envp)
{
	int	i;
	char	*key;
	char	*value;
	t_env	*env_lst;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		key = ft_extract_key(envp[i]);
		value = ft_extract_value(envp[i]);
		ft_update_env_lst(key, value, true, &env_lst);
		i++;
	}
	return (env_lst);
}

t_minishell minishell_init(char **envp)
{
	t_minishell minishell;

	ft_memset(&minishell, 0, sizeof(t_minishell));
	minishell.env_lst = make_env_list(envp);
	minishell.exit_s = EXIT_SUCCESS;
	return (minishell);
}
