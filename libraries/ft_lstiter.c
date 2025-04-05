/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:42:20 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 12:51:53 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}

// #include <ctype.h>
//ccw ft_lstiter_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c
//ft_lstnew_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c
// static void str_toupper(void *p)
// {
// 	int i;

//     char *str = (char *)p;
// 	printf("%s,",str);
// 	i = 0;
//     while (str[i])
//     {
//         str[i] = toupper(str[i]);
//         i++;
//     }
// 	printf("%s\n",str);
// }

// static void cnt_free(void *p)
// {
//     free(p);
// }

// int main()
// {
// 	t_list  *lst = ft_lstnew(strdup("Hello"));

// 	ft_lstadd_back(&lst, ft_lstnew(strdup("World")));
//     ft_lstadd_back(&lst, ft_lstnew(strdup("42")));
//     ft_lstadd_back(&lst, ft_lstnew(strdup("Tokyo!")));
//     ft_lstadd_back(&lst, ft_lstnew(strdup("")));

// 	ft_lstiter(lst, str_toupper);
// 	ft_lstclear(&lst,cnt_free);
// }