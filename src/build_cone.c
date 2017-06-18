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
		e->cones->pos.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cones->pos.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cones->pos.z = (int)ft_atof(ptr->str + 2);
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
		e->cones->rot.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cones->rot.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cones->rot.z = (int)ft_atof(ptr->str + 2);
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
		e->cones->color.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cones->color.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cones->color.z = (int)ft_atof(ptr->str + 2);
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

/* build_angle
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_angle(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_angle");
	char		*sep;

	if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)) == NULL || sep[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	e->cones->angle = ft_atof(sep + 2);
	return (-1);
}

t_str			*build_cone(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_cone");
	t_cone	*old;
	char	**tok;
	int		(*func[4])(t_env*, t_str*) = { build_pos, build_rot, \
											build_color, build_angle };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (4 + 2))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_COLOR);
	tok[3] = ft_strdup(YA_ANGLE);
	tok[4] = NULL;
	tok[5] = ft_strdup("\x0D\0");
	old = e->cones;
	if ((e->cones = (t_cone*)malloc(sizeof(t_cone))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ptr = building_algo(e, ptr, tok, func);
	e->cones->next = old;
	ft_strdel(&(tok[0]));
	ft_strdel(&(tok[1]));
	ft_strdel(&(tok[2]));
	ft_strdel(&(tok[3]));
	ft_strdel(&(tok[5]));
	free(tok);
	tok = NULL;
	ft_putendl("///////////////////////");
	printf("%f\n", e->cones->pos.x);
	printf("%f\n", e->cones->pos.y);
	printf("%f\n", e->cones->pos.z);
	printf("%f\n", e->cones->rot.x);
	printf("%f\n", e->cones->rot.y);
	printf("%f\n", e->cones->rot.z);
	printf("%f\n", e->cones->color.x);
	printf("%f\n", e->cones->color.y);
	printf("%f\n", e->cones->color.z);
	printf("%f\n", e->cones->angle);
	ft_putendl("///////////////////////");
	return (ptr);
}
