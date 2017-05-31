#include <rtv1.h>

void		error_yaml(char *s1, char *s2)
{
	ft_putendl("............");
	ft_putendl(s1);
	ft_errexit(s2, YELLOW, YA_BAD_FORMAT);
}

int		get_token_index(char **tokens, int tok_amount, char *str, char *sep)
{
	int		i;

	sep[0] = 0;
	i = 0;
	while (i < tok_amount)
	{
		if (ft_strcmp(tokens[i], str) == 0)
			break ;
		i++;
	}
	if (i >= tok_amount)
		error_yaml(str, YA_ERROR);
	return (i);
}

void		build_objects(t_env *e, t_str *ptr)
{
	char	*sep;

	while (ptr)
	{
		if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)))
		{
			if (sep[1] != 0 && sep[1] != 32)
				error_yaml(ptr->str, YA_ERROR);
			sep[0] = 0;
			int i = 0;
			while (i < YA_CHART_OBJ)
			{
				if (ft_strcmp(e->chart[i].key_name, ptr->str) == 0)
				{
					ptr = (e->chart[i].func(e, ptr));
					ft_putendl("OOOOOOOOOO");
					ft_putendl(ptr->str);
					ft_putendl("OOOOOOOOOO");
					break ;
				}
				i++;
			}
			if (i == YA_CHART_OBJ)
				error_yaml(ptr->str, YA_ERROR);
		}
		else
			error_yaml(ptr->str, YA_ERROR);
		ptr = ptr->next;
	}
}
