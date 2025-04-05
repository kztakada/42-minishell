/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:56:39 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 12:34:43 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void	*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// static void cnt_free(void *p)
// {
// 	printf("%s\n",(char *)p);
//     free(p);
// }

// int main()
// {
// 	t_list  *node = (t_list *)calloc(sizeof(t_list), 1);
// 	char    *s1 = strdup("hello");
// 	node->content = s1;
// 	ft_lstdelone(node, cnt_free);
// 	//this part will be segf cuz the node was freed.
// 	printf("%d\n",ft_lstsize(node));
// }