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
		e->spheres->pos.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->spheres->pos.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->spheres->pos.z = (int)ft_atof(ptr->str + 2);
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
		e->spheres->rot.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->spheres->rot.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->spheres->rot.z = (int)ft_atof(ptr->str + 2);
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
		e->spheres->color.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->spheres->color.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->spheres->color.z = (int)ft_atof(ptr->str + 2);
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
	e->spheres->r = ft_atof(sep + 2);
	return (-1);
}

t_str			*build_sphere(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_sphere");
	t_sphere	*old;
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
	old = e->spheres;
	if ((e->spheres = (t_sphere*)malloc(sizeof(t_sphere))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ptr = building_algo(e, ptr, tok, func);
	e->spheres->next = old;
	ft_strdel(&(tok[0]));
	ft_strdel(&(tok[1]));
	ft_strdel(&(tok[2]));
	ft_strdel(&(tok[3]));
	ft_strdel(&(tok[5]));
	free(tok);
	tok = NULL;
	ft_putendl("///////////////////////");
	printf("%f\n", e->spheres->pos.x);
	printf("%f\n", e->spheres->pos.y);
	printf("%f\n", e->spheres->pos.z);
	printf("%f\n", e->spheres->rot.x);
	printf("%f\n", e->spheres->rot.y);
	printf("%f\n", e->spheres->rot.z);
	printf("%f\n", e->spheres->color.x);
	printf("%f\n", e->spheres->color.y);
	printf("%f\n", e->spheres->color.z);
	printf("%f\n", e->spheres->r);
	ft_putendl("///////////////////////");
	return (ptr);
}
