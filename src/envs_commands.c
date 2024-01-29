#include "../includes/minishell.h"


void	printenv(t_entry *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	printf("\n");
}

void	printexport(t_entry  *exp)
{
	while (exp != NULL)
	{
		printf("%s=\"%s\"\n", exp->name, exp->value);
		exp = exp->next;
	}
	printf("\n");
}
