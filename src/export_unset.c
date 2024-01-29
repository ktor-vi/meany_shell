#include "../includes/minishell.h"

t_entry	*only_exp_entry(char *var)
{
	t_entry	*new;
	size_t	eq_pos;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->name = ft_strdup(var);
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	export_cmd(t_envs *envs, char *var)
{
	t_entry	*new;
	int	eq_pos;

	new = malloc(sizeof(t_entry));
	eq_pos = getchindex(var, '=');
	new->next = NULL;
	if (!new || !envs || !var)
		return ;
	if (eq_pos < 0)
	{
		envs->exp_ct++;
		ft_entry_addb(&envs->exp, only_exp_entry(var));
	}
	else
	{
		ft_entry_addb(&envs->env, newentry(var));
		ft_entry_addb(&envs->exp, newentry(var));
		envs->exp_ct++;
		envs->env_ct++;
		sort_alpha_ll(&envs->exp, envs->exp_ct);
	}
}
