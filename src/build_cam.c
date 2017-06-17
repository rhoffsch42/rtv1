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
		e->cam.pos.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cam.pos.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cam.pos.z = (int)ft_atof(ptr->str + 2);
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 3)
		return (-1);
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
		e->cam.rot.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cam.rot.y = (int)ft_atof(ptr->str + 2);
	else if (o == 2)
		e->cam.rot.z = (int)ft_atof(ptr->str + 2);
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 3)
		return (-1);
	return (1);
}

/* build_step
** 1er check: ne start pas par "- " ou n'est que "- "
*/

static int		build_step(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_step");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->cam.step.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cam.step.y = (int)ft_atof(ptr->str + 2);
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	if (o == 2)
		return (-1);
	return (2);
}

t_str			*build_cam(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_cam");
	char	**tok;
	int		(*func[3])(t_env*, t_str*) = { build_pos, build_rot, build_step };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * 4)) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_STEP);
	tok[3] = NULL;
	tok[4] = ft_strdup("\x0B\0");
	ptr = building_algo(e, ptr, tok, func);
	ft_strdel(&(tok[0]));
	ft_strdel(&(tok[1]));
	ft_strdel(&(tok[2]));
	ft_strdel(&(tok[4]));
	free(tok);
	tok = NULL;
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
