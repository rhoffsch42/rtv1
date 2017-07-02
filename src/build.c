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

void		build_objects(t_env *e, t_str *p, int id)
{
	char	*s;
	int		i;

	while (p)
	{
		if ((s = ft_strchr(p->str, YA_SEPARATOR)) && !(i = 0))
		{
			(s[1] != 0 && s[1] != 32) ? error_yaml(p->str, YA_ERROR) : (void)i;
			s[0] = 0;
			while (i < YA_CHART_OBJ)
			{
				if (ft_strcmp(e->chart[i].key_name, p->str) == 0)
				{
					s[0] = YA_SEPARATOR;
					p = (e->chart[i].func(e, p, id++));
					break ;
				}
				i++;
			}
			(i == YA_CHART_OBJ) ? error_yaml(p->str, YA_ERROR) : (void)i;
		}
		else
			error_yaml(p->str, YA_ERROR);
		p = p->next;
	}
}
