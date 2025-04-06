/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:43:50 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 12:51:12 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// static void	print_list(t_list *list)
// {
// 	while (list != NULL)
// 	{
// 		printf("%s -> ", (char *)list->content);
// 		list = list->next;
// 	}
// 	printf("NULL\n");
// }

// int main()
// {
// 	t_list	*list = NULL;
// 	ft_lstadd_front(&list, ft_lstnew("three"));
// 	ft_lstadd_front(&list, ft_lstnew("two"));
//     ft_lstadd_front(&list, ft_lstnew("one"));
// 	print_list(list);
// 	printf("%d\n",ft_lstsize(list));
// }