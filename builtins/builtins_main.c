#include "../includes/h_minishell.h"

int	app_main(int argc, char *argv[])
{
	printf("Hello, World!\n");
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