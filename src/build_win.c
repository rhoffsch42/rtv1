#include <rtv1.h>

float	ft_atof(char *s)
{
	(void)s;
	return (777);
}

void	check_build_title(t_env *e, t_str *ptr, char *i, char *sep)
{
	if (i[1] == 0)
	{
		if (sep[1] != 32)
			error_yaml(ptr->str, YA_ERROR);
		e->sdl->title = ft_strdup(sep + 2);
		i[1] = -1;
	}
	else
		i[2] = 0;
}

void	build_size(t_env *e, t_str *ptr, char *i)
{
	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != 32)
		error_yaml(ptr->str, YA_ERROR);
	if (i[2] == 0)
		e->sdl->win_x = (int)ft_atof(ptr->str + 2);
	else
		e->sdl->win_y = (int)ft_atof(ptr->str + 2);
	i[2]++;
	if (i[2] == 2)
	{
		i[1] = -1;
		i[2] = -1;
	}
}

t_str	*build_win(t_env *e, t_str *ptr)
{
	char	*tokens[2];
	char	i[3];
	char	*sep;

	ptr = ptr->next;
	tokens[0] = YA_TITLE;
	tokens[1] = YA_SIZE;
	i[0] = 0;
	i[1] = -1;
	i[2] = -1;
	while (i[0] < 4)
	{
		if (i[1] == -1 && (sep = ft_strchr(ptr->str, YA_SEPARATOR)))
		{
			i[1] = get_token_index(tokens, 2, ptr->str, sep);
			check_build_title(e, ptr, i, sep);
		}
		else if (i[1] == 1)
			build_size(e, ptr, i);
		else
			error_yaml(ptr->str, YA_ERROR);
		i[0]++;
		ptr = (i[0] < 4) ? ptr->next : ptr;
	}
	return (ptr);
}
