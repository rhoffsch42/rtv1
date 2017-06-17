#include <rtv1.h>

// void	check_build_title(t_env *e, t_str *ptr, char *i, char *sep)
// {
// 	if (i[1] == 0)
// 	{
// 		if (sep[1] != 32)
// 			error_yaml(ptr->str, YA_ERROR);
// 		e->sdl->title = ft_strdup(sep + 2);
// 		i[1] = -1;
// 	}
// 	else
// 		i[2] = 0;
// }
//
// void	build_size(t_env *e, t_str *ptr, char *i)
// {
// 	//if ne start pas par "- " || n'est que "- "
// 	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
// 		error_yaml(ptr->str, YA_ERROR);
// 	if (i[2] == 0)
// 		e->sdl->win_x = (int)ft_atof(ptr->str + 2);
// 	else if (i[2] == 1)
// 		e->sdl->win_y = (int)ft_atof(ptr->str + 2);
// 	else
// 		error_yaml(ptr->str, YA_ERROR);
// 	i[2]++;
// 	if (i[2] == 2)
// 	{
// 		i[1] = -1;
// 		i[2] = -1;
// 	}
// }

// t_str	*build_win(t_env *e, t_str *ptr)
// {
// 	ft_putendl("- - - - - -build_win");
// 	char	*tokens[2];
// 	char	i[3];
// 	char	*sep;
//
// 	ptr = check_no_value(ptr);
// 	tokens[0] = YA_TITLE;
// 	tokens[1] = YA_SIZE;
// 	i[0] = 0;//inc
// 	i[1] = -1;//profondeur 1
// 	i[2] = -1;//profondeur 2
// 	while (i[0] < 4)
// 	{
// 		if (i[1] == -1 && (sep = ft_strchr(ptr->str, YA_SEPARATOR)))
// 		{
// 			i[1] = get_token_index(tokens, 2, ptr->str, sep);
// 			check_build_title(e, ptr, i, sep);
// 		}
// 		else if (i[1] == 1)
// 			build_size(e, ptr, i);
// 		else
// 			error_yaml(ptr->str, YA_ERROR);
// 		i[0]++;
// 		ptr = (i[0] < 4) ? ptr->next : ptr;
// 	}
// 	return (ptr);
// }

static int		build_size(t_env *e, t_str *ptr)
{
	static int	i = 0;

	//if ne start pas par "- " || n'est que "- "
	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (i == 0)
		e->sdl->win_x = (int)ft_atof(ptr->str + 2);
	else if (i == 1)
		e->sdl->win_y = (int)ft_atof(ptr->str + 2);
	else
		error_yaml(ptr->str, YA_ERROR);
	i++;
	if (i == 2)
		return (-1);
	return (0);
}

static int		build_title(t_env *e, t_str *ptr)
{
	char		*sep;

	if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)) == NULL || sep[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	// ajouter une verification: sep + 2 n'est pas vide
	e->sdl->title = ft_strdup(sep + 2);
	return (-1);
}

t_str	*build_win(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_win");
	int		(*func[2])(t_env*, t_str*) = {build_size, build_title};
	char	*tok[2];
	char	i[2];
	char	*sep;

	ptr = check_no_value(ptr);
	tok[0] = YA_SIZE;
	tok[1] = YA_TITLE;
	i[0] = 0;//inc
	i[1] = -1;//profondeur 1
	while (i[0] < 4)
	{
		if (i[1] == -1 && (sep = ft_strchr(ptr->str, YA_SEPARATOR)))
		{
			i[1] = get_token_index(tok, 2, ptr->str, sep);
			if (e->chart[get_chart_index(e, tok[(int)i[1]])].val_amount == 1)
				i[1] = func[(int)i[1]](e, ptr);
		}
		else if (!(i[1] >= 0 && i[1] <= 1))
			error_yaml(ptr->str, YA_ERROR);
		else
			i[1] = func[(int)i[1]](e, ptr);
		// on passe a la struct suivante si on a pas de token a une seule value
		// ou qu on est pas a la derniere ligne
		i[0]++;
		ptr = (i[0] < 11) ? ptr->next : ptr;
	}
	ft_putendl("///////////////////////////");
	ft_putnbr(e->sdl->win_x);ENDL
	ft_putnbr(e->sdl->win_y);ENDL
	ft_putendl(e->sdl->title);
	ft_putendl("///////////////////////////");
	return (ptr);
	// while (i[0] < 4)
	// {
	// 	ft_putendl(ptr->str);
	// 	if (i[1] == -1 && (sep = ft_strchr(ptr->str, YA_SEPARATOR)))
	// 		i[1] = get_token_index(tok, 2, ptr->str, sep);
	// 	else if (!(i[1] >= 0 && i[1] <= 1))
	// 		error_yaml(ptr->str, YA_ERROR);
	// 	else
	// 		i[1] = func[(int)i[1]](e, ptr);
	// 	// on passe a la struct suivante si on a pas de token a une seule value
	// 	// ou qu on est pas a la derniere ligne
	// 	if (i[1] == -1 || e->chart[get_chart_index(e, tok[(int)i[1]])].val_amount != 1)
	// 	{
	// 		i[0]++;
	// 		ptr = (i[0] < 11) ? ptr->next : ptr;
	// 	}
	// }
}
