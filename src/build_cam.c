#include <rtv1.h>

/* build_pos
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_pos_cam(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_pos");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->cam.pos.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->cam.pos.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->cam.pos.z = ft_atof(secure_atof(ptr->str + 2));
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

static int		build_rot_cam(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_rot");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->cam.rot.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->cam.rot.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->cam.rot.z = ft_atof(secure_atof(ptr->str + 2));
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

/* build_step
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_step_cam(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_step");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->cam.step.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->cam.step.y = ft_atof(secure_atof(ptr->str + 2));
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 2)
	{
		o = 0;
		return (-1);
	}
	return (2);
}

t_str			*build_cam(t_env *e, t_str *ptr, int id)
{
	ft_putendl("- - - - - -build_cam");
	char	**tok;
	int		(*func[3])(t_env*, t_str*) = { build_pos_cam, build_rot_cam, build_step_cam };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * 5)) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	e->cam.id = id;
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_STEP);
	tok[3] = NULL;
	tok[4] = ft_strdup("\x0B\0");
	ptr = building_algo(e, ptr, tok, func);
	ft_strdel(&(tok[4]));
	ft_tabdel(&tok);
	ft_putendl("///////////////////////");
	ft_putnbr(e->cam.pos.x);ENDL
	ft_putnbr(e->cam.pos.y);ENDL
	ft_putnbr(e->cam.pos.z);ENDL
	ft_putnbr(e->cam.rot.x);ENDL
	ft_putnbr(e->cam.rot.y);ENDL
	ft_putnbr(e->cam.rot.z);ENDL
	ft_putnbr(e->cam.step.x);ENDL
	ft_putnbr(e->cam.step.y);ENDL
	ft_putendl("///////////////////////");
	return (ptr);
}
