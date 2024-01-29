#include "./libft/libft.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_entry
{
	char			*name;
	char			*value;
	struct s_entry	*next;
	struct s_entry	*prev;
}					t_entry;

typedef struct s_envs
{
	struct s_entry	*env;
	struct s_entry	*exp;
	size_t			env_ct;
	size_t			exp_ct;

}					t_envs;

t_entry	*swap(t_entry *ptr1, t_entry *ptr2)
{
	t_entry	*tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	return (ptr2);
}

void	sort_alpha_ll(t_entry **head, int count)
{
	int		i;
	t_entry	**h;
	int		swapped;
	int		j;
	t_entry	*p1;
	t_entry	*p2;

	i = 0;
	while (i <= count)
	{
		h = head;
		swapped = 0;
		j = 0;
		while (j < count - i - 1)
		{
			p1 = *h;
			p2 = p1->next;
			if (strcmp(p1->name, p2->name) > 0)
			{
				*h = swap(p1, p2);
				swapped = 1;
			}
			h = &(*h)->next;
			j++;
		}
		if (swapped == 0)
			break ;
		i++;
	}
}

t_entry  *lastentry(t_entry *lst)
{
        t_entry  *ptr;

        ptr = lst;
        if (ptr == NULL)
                return (NULL);
        while (ptr->next != NULL)
                ptr = ptr->next;
        return (ptr);
}

void	ft_entry_addb(t_entry **lst, t_entry *new)
{
        t_entry  *last;

        if (new == NULL)
                return ;
        last = lastentry(*lst);
        if (last != NULL)
        {
                last->next = new;
                new->prev = last;
        }
        else
                *lst = new;
}
void	printenv(t_entry *n)
{
	while (n != NULL)
	{
		printf("%s=\"%s\"\n", n->name, n->value);
		n = n->next;
	}
	printf("\n");
}

int	getchindex(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_entry	*newentry(char *var)
{
	t_entry	*new;
	size_t	eq_pos;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	eq_pos = getchindex(var, '=');
	new->name = ft_substr(var, 0, eq_pos);
	new->value = ft_substr(var, eq_pos + 1, ft_strlen(var) - eq_pos);
	new->prev= NULL;
	new->next = NULL;
	return (new);
}

t_envs	*build_envs(char **envp)
{
	t_envs	*envs;
	int		i;

	i = 0;
	envs = malloc(sizeof(t_envs));
	envs->env = NULL;
	envs->exp = NULL;
	while (envp[i])
	{
		ft_entry_addb(&envs->env, newentry(envp[i]));
		ft_entry_addb(&envs->exp, newentry(envp[i]));
		i++;
	}
	sort_alpha_ll(&envs->exp, i);
	envs->env_ct = i;
	envs->exp_ct = i;
	return (envs);
}

void free_envs(t_envs **envs)
{
	t_entry *tmp;

	while((*envs)->env->next)
	{
                tmp = (*envs)->env;
                (*envs)->env = (*envs)->env->next;
    						free(tmp->name);
    						free(tmp->value);
                free(tmp);
	}
	while((*envs)->exp->next)
	{
                tmp = (*envs)->exp;
                (*envs)->exp = (*envs)->exp->next;
    						free(tmp->name);
    						free(tmp->value);
                free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envs *envs;

	(void)argc;
	(void)argv;
	 envs = NULL;
	envs = build_envs(envp);
	printf("Env\n");
	printenv(envs->env);
	printf("Export\n");
	printenv(envs->exp);
	free_envs(&envs);
	system("leaks a.out");
	return (0);
}
