#include <rtv1.h>

void		error_yaml(char *s1, char *s2)
{
	ft_putendl("________ERROR YAML________");
	ft_putendl(s1);
	ft_errexit(s2, YELLOW, YA_BAD_FORMAT);
}

t_str	*check_no_value(t_str *ptr)
{
	char	*s;

	ft_putendl(ptr->str);
	s = ft_strchr(ptr->str, YA_SEPARATOR);
	if (s[1] != 0)
		error_yaml(ptr->str, YA_ERROR);
	return (ptr->next);
}

char		*secure_atof(char *s)
{
	int		i;
	int		len;
	int		point;

	point = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	len = (i == 0) ? ft_strlen(s) : ft_strlen(s) - 1;
	if (len > FLOAT_MAX_LEN)
		error_yaml(s, YA_BAD_FLOAT);
	while (s[i])
	{
		if (s[i] == '.')
		{
			point++;
			i++;
		}
		if (!ft_isdigit(s[i]))
			error_yaml(s, YA_BAD_FLOAT);
		i++;
	}
	if (point > 1)
		error_yaml(s, YA_BAD_FLOAT);
	return (s);
}

void		build_objects(t_env *e, t_str *ptr)
{
	char	*sep;

	while (ptr)
	{
		// ft_putendl("build next");ft_putendl(ptr->str);
		if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)))
		{
			if (sep[1] != 0 && sep[1] != 32)
				error_yaml(ptr->str, YA_ERROR);
			sep[0] = 0;
			int i = 0;
			while (i < YA_CHART_OBJ)
			{
				// ft_putchar(':');
				if (ft_strcmp(e->chart[i].key_name, ptr->str) == 0)
				{
					sep[0] = YA_SEPARATOR;
					ptr = (e->chart[i].func(e, ptr));
					// ft_putendl("OOOOOOOOOO");
					// ft_putendl(ptr->str);
					// ft_putendl	("OOOOOOOOOO");
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
