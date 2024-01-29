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
		if(exp->value)
			printf("declare -x %s=\"%s\"\n", exp->name, exp->value);
		else
			printf("declare -x %s\n", exp->name);
		exp = exp->next;
	}
	printf("\n");
}
