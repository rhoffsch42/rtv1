#include <rtv1.h>

t_str			*build_sphere(t_env *e, t_str *ptr, int id)
{
	ft_putendl("- - - - - -build_sphere");
	t_obj	*old;
	char	**tok;
	int		(*func[4])(t_env*, t_str*) = { build_pos, build_rot, build_color, build_param };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (4 + 2))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_COLOR);
	tok[3] = ft_strdup(YA_RAY);
	tok[4] = NULL;
	tok[5] = ft_strdup("\x0D\0");
	old = e->objs;
	if ((e->objs = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	e->objs->type = SPHERE;
	e->objs->id = id;
	ptr = building_algo(e, ptr, tok, func);
	e->objs->next = old;
	ft_strdel(&(tok[5]));
	ft_tabdel(&tok);
	ft_putendl("///////////////////////");
	printf("%f\n", e->objs->pos.x);
	printf("%f\n", e->objs->pos.y);
	printf("%f\n", e->objs->pos.z);
	printf("%f\n", e->objs->rot.x);
	printf("%f\n", e->objs->rot.y);
	printf("%f\n", e->objs->rot.z);
	printf("%f\n", e->objs->color.x);
	printf("%f\n", e->objs->color.y);
	printf("%f\n", e->objs->color.z);
	printf("%f\n", e->objs->param);
	ft_putendl("///////////////////////");
	return (ptr);
}

t_str			*build_cylinder(t_env *e, t_str *ptr, int id)
{
	ft_putendl("- - - - - -build_cylinder");
	t_obj	*old;
	char	**tok;
	int		(*func[4])(t_env*, t_str*) = { build_pos, build_rot, \
											build_color, build_param };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (4 + 2))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_COLOR);
	tok[3] = ft_strdup(YA_RAY);
	tok[4] = NULL;
	tok[5] = ft_strdup("\x0D\0");
	old = e->objs;
	if ((e->objs = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	e->objs->type = CYLINDER;
	e->objs->id = id;
	ptr = building_algo(e, ptr, tok, func);
	e->objs->next = old;
	ft_strdel(&(tok[5]));
	ft_tabdel(&tok);
	ft_putendl("///////////////////////");
	printf("%f\n", e->objs->pos.x);
	printf("%f\n", e->objs->pos.y);
	printf("%f\n", e->objs->pos.z);
	printf("%f\n", e->objs->rot.x);
	printf("%f\n", e->objs->rot.y);
	printf("%f\n", e->objs->rot.z);
	printf("%f\n", e->objs->color.x);
	printf("%f\n", e->objs->color.y);
	printf("%f\n", e->objs->color.z);
	printf("%f\n", e->objs->param);
	ft_putendl("///////////////////////");
	return (ptr);
}

t_str			*build_cone(t_env *e, t_str *ptr, int id)
{
	ft_putendl("- - - - - -build_cone");
	t_obj	*old;
	char	**tok;
	int		(*func[4])(t_env*, t_str*) = { build_pos, build_rot, \
											build_color, build_param };

	ptr = check_no_value(ptr);
	if ((tok = (char**)malloc(sizeof(char*) * (4 + 2))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	tok[0] = ft_strdup(YA_POS);
	tok[1] = ft_strdup(YA_ROT);
	tok[2] = ft_strdup(YA_COLOR);
	tok[3] = ft_strdup(YA_ANGLE);
	tok[4] = NULL;
	tok[5] = ft_strdup("\x0D\0");
	old = e->objs;
	if ((e->objs = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	e->objs->type = CONE;
	e->objs->id = id;
	ptr = building_algo(e, ptr, tok, func);
	e->objs->next = old;
	ft_strdel(&(tok[5]));
	ft_tabdel(&tok);
	ft_putendl("///////////////////////");
	printf("%f\n", e->objs->pos.x);
	printf("%f\n", e->objs->pos.y);
	printf("%f\n", e->objs->pos.z);
	printf("%f\n", e->objs->rot.x);
	printf("%f\n", e->objs->rot.y);
	printf("%f\n", e->objs->rot.z);
	printf("%f\n", e->objs->color.x);
	printf("%f\n", e->objs->color.y);
	printf("%f\n", e->objs->color.z);
	printf("%f\n", e->objs->param);
	ft_putendl("///////////////////////");
	return (ptr);
}

t_str			*build_plan(t_env *e, t_str *ptr, int id)
{
	ft_putendl("- - - - - -build_plan");
	t_obj	*old;
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
	old = e->objs;
	if ((e->objs = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	e->objs->type = PLAN;
	e->objs->id = id;
	e->objs->param = -1;
	ptr = building_algo(e, ptr, tok, func);
	e->objs->next = old;
	ft_strdel(&(tok[4]));
	ft_tabdel(&tok);
	ft_putendl("///////////////////////");
	printf("%f\n", e->objs->pos.x);
	printf("%f\n", e->objs->pos.y);
	printf("%f\n", e->objs->pos.z);
	printf("%f\n", e->objs->rot.x);
	printf("%f\n", e->objs->rot.y);
	printf("%f\n", e->objs->rot.z);
	printf("%f\n", e->objs->color.x);
	printf("%f\n", e->objs->color.y);
	printf("%f\n", e->objs->color.z);
	ft_putendl("///////////////////////");
	return (ptr);
}
