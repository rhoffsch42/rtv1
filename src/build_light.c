#include <rtv1.h>

/* build_pos
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_pos_light(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_pos");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->lights->pos.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->lights->pos.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->lights->pos.z = ft_atof(secure_atof(ptr->str + 2));
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

static int		build_rot_light(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_rot");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->lights->rot.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->lights->rot.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->lights->rot.z = ft_atof(secure_atof(ptr->str + 2));
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

/* build_intensity
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_intensity(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_intensity");
	char		*sep;

	if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)) == NULL || sep[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	e->lights->intensity = ft_atof(secure_atof(sep + 2));
	return (-1);
}

t_str			*build_light(t_env *e, t_str *ptr, int id)
{
	ft_putendl("- - - - - -build_cone");
	t_light	*old;
	char	**tok;
	int		(*func[3])(t_env*, t_str*) = { build_pos_light, build_rot_light, build_intensity };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (3 + 2))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_INTENSITY);
	tok[3] = NULL;
	tok[4] = ft_strdup("\x09\0");
	old = e->lights;
	if ((e->lights = (t_light*)malloc(sizeof(t_light))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ptr = building_algo(e, ptr, tok, func);
	e->lights->next = old;
	e->lights->id = id;
	ft_strdel(&(tok[4]));
	ft_tabdel(&tok);
	ft_putendl("///////////////////////");
	printf("%f\n", e->lights->pos.x);
	printf("%f\n", e->lights->pos.y);
	printf("%f\n", e->lights->pos.z);
	printf("%f\n", e->lights->rot.x);
	printf("%f\n", e->lights->rot.y);
	printf("%f\n", e->lights->rot.z);
	printf("%f\n", e->lights->intensity);
	ft_putendl("///////////////////////");
	return (ptr);
}
