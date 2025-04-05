/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:42:48 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/15 23:57:28 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	temp = NULL;
	if (*lst)
	{
		temp = *lst;
		ft_lstlast(*lst)->next = new;
		*lst = temp;
	}
	else
		*lst = new;
}

// static void print_addback(t_list *actual, t_list *expected)
// {
// 	if(!actual)
// 		return ;
// 	printf("actual: ");
// 	while (actual->next)
// 	{
// 		printf("%s -> ",(char *)actual->content);
// 		actual = actual->next;
// 	}
// 	printf("NULL\n");
// 	printf("expected: ");
// 	while (expected->next)
// 	{
// 		printf("%s -> ",(char *)expected->content);
// 		expected = expected->next;
// 	}
// 	printf("NULL\n\n");
// }

// int	main(void)
// {
//     t_list  *lst = NULL;
//     t_list  *node1 = calloc(sizeof(t_list), 1);
//     t_list  *node2 = calloc(sizeof(t_list), 1);
//     t_list  *node3 = calloc(sizeof(t_list), 1);
//     t_list  *node4 = calloc(sizeof(t_list), 1);
//     t_list  *node5 = calloc(sizeof(t_list), 1);
//     char    *s1 = "hello";
//     char    *s2 = "world";
//     char    *s3 = "42!";
//     int     val4 = 42;
//     int     val5 = -42;
//     node1->content = s1;
//     node2->content = s2;
//     node3->content = s3;
//     node4->content = &val4;
//     node5->content = &val5;

//     ft_lstadd_back(&lst, node1);
//     print_addback(lst, node1);

//     ft_lstadd_back(&lst, node2);
//     print_addback(lst, node1);

//     ft_lstadd_back(&lst, node3);
//     print_addback(lst, node1);

//     ft_lstadd_back(&lst, node4);
//     print_addback(lst, node1);

//     ft_lstadd_back(&lst, node5);
//     print_addback(lst, node1);

// 	return (0);
// }