#include "../includes/minishell.h"

t_entry	*newentry(char *var)
{
	t_entry	*new;
	int		eq_pos;
	int		offset;

	offset = 0;
	new = ft_calloc(1, sizeof(t_entry));
	if (!new)
		return (NULL);
	eq_pos = getchindex(var, '=');
	if (var[eq_pos - 1] == '+')
		offset = 1;
	new->name = ft_substr(var, 0, eq_pos - offset);
	new->value = ft_substr(var, eq_pos + 1, ft_strlen(var) - eq_pos);
	new->name = ft_strtrim(ft_strtrim(new->name, "\""), "\'");
	new->value = ft_strtrim(ft_strtrim(new->value, "\""), "\'");
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_entry	*swap(t_entry *ptr1, t_entry *ptr2)
{
	t_entry	*tmp;

	tmp = ptr2->next;
	ptr2->next = ptr1;
	ptr1->next = tmp;
	ptr1->prev = ptr2;
	ptr2->prev = ptr1;

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

t_entry	*lastentry(t_entry *lst)
{
	t_entry	*ptr;

	ptr = lst;
	if (ptr == NULL)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_entry_addb(t_entry **lst, t_entry *new)
{
	t_entry	*last;

	if (new == NULL)
		return ;
	last = lastentry(*lst);
	new->prev = last;
	if (last != NULL)
		last->next = new;
	else
		*lst = new;
}
