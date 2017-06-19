#include <rtv1.h>

/* build_size
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_size(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_size");
	static int	o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->sdl->win_x = (int)ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->sdl->win_y = (int)ft_atof(secure_atof(ptr->str + 2));
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 2)
	{
		o = 0;
		return (-1);
	}
	return (0);
}

/* build_title
** ajouter une verification? sep + 2 ne doit pas etre vide
*/

static int		build_title(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_title");
	char		*sep;

	if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)) == NULL || sep[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	e->sdl->title = ft_strdup(sep + 2);
	return (-1);
}

/* build_win
** tok = malloc(x + 1)
** on rajoute le nombre de lignes (pour l'objet) needed dans building_algo()
*/

t_str	*build_win(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_win");
	int		(*func[2])(t_env*, t_str*) = {build_size, build_title};
	char	**tok;

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (3 + 1))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_SIZE);
	tok[1] = ft_strdup(YA_TITLE);
	tok[2] = NULL;
	tok[3] = ft_strdup("\x04\0");
	ptr = building_algo(e, ptr, tok, func);
	ft_strdel(&(tok[0]));
	ft_strdel(&(tok[1]));
	ft_strdel(&(tok[3]));
	free(tok);
	tok = NULL;
	ft_putendl("///////////////////////////");
	ft_putnbr(e->sdl->win_x);ENDL
	ft_putnbr(e->sdl->win_y);ENDL
	ft_putendl(e->sdl->title);
	ft_putendl("///////////////////////////");
	return (ptr);
}
