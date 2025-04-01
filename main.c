/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/04/01 17:29:31 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	sum(int a, int b)
{
	return (a + b);
}

int	app_main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	return (0);
}

#ifndef TEST

int	main(int argc, char *argv[])
{
	return (app_main(argc, argv));
}
#endif // TEST