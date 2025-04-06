/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:42:11 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 17:56:05 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, node);
		lst = lst->next;
	}
	return (new);
}

// #include <ctype.h>

// ccw ft_lstmap_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c
//ft_lstnew_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c
// static void *str_toupper(void *p)
// {
//     char *str = strdup((char *)p);
//     char *tmp = str;
// 	printf("%s -> ",str);
//     while (*tmp)
//     {
//         *tmp = toupper(*tmp);
//         tmp++;
//     }
// 	printf("%s\n",str);
//     return (str);
// }

// int main()
// {
//     t_list  *lst = ft_lstnew(strdup("Hello"));
//     ft_lstadd_back(&lst, ft_lstnew(strdup("World")));
//     ft_lstadd_back(&lst, ft_lstnew(strdup("42")));
//     ft_lstadd_back(&lst, ft_lstnew(strdup("Tokyo!")));

// 	t_list *newlst = ft_lstmap(lst, str_toupper, free);
// 	ft_lstclear(&newlst,free);
// }