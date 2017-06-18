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
		e->cylinders->pos.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cylinders->pos.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cylinders->pos.z = (int)ft_atof(ptr->str + 2);
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
		e->cylinders->rot.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cylinders->rot.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cylinders->rot.z = (int)ft_atof(ptr->str + 2);
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
		e->cylinders->color.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cylinders->color.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cylinders->color.z = (int)ft_atof(ptr->str + 2);
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

/* build_ray** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_ray(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_ray");
	char		*sep;

	if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)) == NULL || sep[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	e->cylinders->r = ft_atof(sep + 2);
	return (-1);
}

t_str			*build_cylinder(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_cylinder");
	t_cylinder	*old;
	char	**tok;
	int		(*func[4])(t_env*, t_str*) = { build_pos, build_rot, \
											build_color, build_ray };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (4 + 2))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_COLOR);
	tok[3] = ft_strdup(YA_RAY);
	tok[4] = NULL;
	tok[5] = ft_strdup("\x0D\0");
	old = e->cylinders;
	if ((e->cylinders = (t_cylinder*)malloc(sizeof(t_cylinder))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ptr = building_algo(e, ptr, tok, func);
	e->cylinders->next = old;
	ft_strdel(&(tok[0]));
	ft_strdel(&(tok[1]));
	ft_strdel(&(tok[2]));
	ft_strdel(&(tok[3]));
	ft_strdel(&(tok[5]));
	free(tok);
	tok = NULL;
	ft_putendl("///////////////////////");
	printf("%f\n", e->cylinders->pos.x);
	printf("%f\n", e->cylinders->pos.y);
	printf("%f\n", e->cylinders->pos.z);
	printf("%f\n", e->cylinders->rot.x);
	printf("%f\n", e->cylinders->rot.y);
	printf("%f\n", e->cylinders->rot.z);
	printf("%f\n", e->cylinders->color.x);
	printf("%f\n", e->cylinders->color.y);
	printf("%f\n", e->cylinders->color.z);
	printf("%f\n", e->cylinders->r);
	ft_putendl("///////////////////////");
	return (ptr);
}
