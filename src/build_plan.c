#include <rtv1.h>

/* build_pos
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_pos(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_pos");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->plans->pos.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->plans->pos.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->plans->pos.z = ft_atof(secure_atof(ptr->str + 2));
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 3)
	{
		o = 0;
		return (-1);
	}
	return (0);
}

/* build_rot
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_rot(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_rot");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->plans->rot.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->plans->rot.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->plans->rot.z = ft_atof(secure_atof(ptr->str + 2));
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 3)
	{
		o = 0;
		return (-1);
	}
	return (1);
}

/* build_color
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_color(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_color");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->plans->color.x = (int)ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->plans->color.y = (int)ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->plans->color.z = (int)ft_atof(secure_atof(ptr->str + 2));
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 3)
	{
		o = 0;
		return (-1);
	}
	return (2);
}

t_str			*build_plan(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_plan");
	t_plan	*old;
	char	**tok;
	int		(*func[3])(t_env*, t_str*) = { build_pos, build_rot, build_color };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (3 + 2))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_COLOR);
	tok[3] = NULL;
	tok[4] = ft_strdup("\x0C\0");
	old = e->plans;
	if ((e->plans = (t_plan*)malloc(sizeof(t_plan))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ptr = building_algo(e, ptr, tok, func);
	e->plans->next = old;
	ft_strdel(&(tok[0]));
	ft_strdel(&(tok[1]));
	ft_strdel(&(tok[2]));
	ft_strdel(&(tok[4]));
	free(tok);
	tok = NULL;
	ft_putendl("///////////////////////");
	printf("%f\n", e->plans->pos.x);
	printf("%f\n", e->plans->pos.y);
	printf("%f\n", e->plans->pos.z);
	printf("%f\n", e->plans->rot.x);
	printf("%f\n", e->plans->rot.y);
	printf("%f\n", e->plans->rot.z);
	printf("%f\n", e->plans->color.x);
	printf("%f\n", e->plans->color.y);
	printf("%f\n", e->plans->color.z);
	ft_putendl("///////////////////////");
	return (ptr);
}
