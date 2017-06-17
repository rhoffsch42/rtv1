#include <rtv1.h>

static int		build_pos(t_env *e, t_str *ptr)
{
	ft_putendl("build cam pos");
	static char		o = 0;

	//if ne start pas par "- " || n'est que "- "
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
	ft_putendl("____");
	if (o == 3)
		return (-1);
	return (0);
}

static int		build_rot(t_env *e, t_str *ptr)
{
	static char		o = 0;

	ft_putendl("build cam rot");
	//if ne start pas par "- " || n'est que "- "
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
	ft_putendl("____");
	if (o == 3)
		return (-1);
	return (1);
}

static int		build_step(t_env *e, t_str *ptr)
{
	static char		o = 0;

	ft_putendl("build cam step");
	//if ne start pas par "- " || n'est que "- "
	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->cam.step.x = (int)ft_atof(ptr->str + 2);
	else if (o == 1)
		e->cam.step.y = (int)ft_atof(ptr->str + 2);
	else
		error_yaml(ptr->str, YA_ERROR);
	o++;
	ft_putendl("____");
	if (o == 2)
		return (-1);
	return (2);
}

t_str			*build_cam(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_cam");
	char	*tokens[3];
	char	*sep;
	char	i[2];
	int		(*func[3])(t_env*, t_str*) = { build_pos, build_rot, build_step };

	ptr = check_no_value(ptr);
	// func[0] = build_pos;
	// func[1] = build_rot;
	// func[2] = build_step;
	tokens[0] = YA_POS;
	tokens[1] = YA_ROT;
	tokens[2] = YA_STEP;
	i[0] = 0;
	i[1] = -1;//profondeur 1
	while (i[0] < 11)
	{
		if (i[1] == -1 && (sep = ft_strchr(ptr->str, YA_SEPARATOR)))
			i[1] = get_token_index(tokens, 3, ptr->str, sep);
		else if (!(i[1] >= 0 && i[1] <= 2))
			error_yaml(ptr->str, YA_ERROR);
		else
			i[1] = func[(int)i[1]](e, ptr);
		i[0]++;
		ptr = (i[0] < 11) ? ptr->next : ptr;
	}
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
