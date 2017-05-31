#include <rtv1.h>

int			is_empty(LIST_TYPE ptr)
{
	if (ft_strlen(ptr->str) == 0)
		return (1);
	return (0);
}

LIST_TYPE	remove_list(LIST_TYPE ptr, int (f)(LIST_TYPE))
{
	LIST_TYPE	before;
	LIST_TYPE	current;

	if (!(before = NULL) && (current = ptr))
		while (current)
			if (f(current) && before == NULL)
			{
					free(current->str);
					ptr = current->next;
					free(current);
					current = ptr;
			}
			else
			{
				if (f(current))
				{
						free(current->str);
						before->next = current->next;
						free(current);
				}
				else
					before = current;
				current = before->next;
			}
	return (ptr);
}
