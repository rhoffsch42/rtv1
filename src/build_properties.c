#include <rtv1.h>

/* build_pos
** 1er check: ne start pas par "- " ou n'est que "- "
*/

int		build_pos(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_pos");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->objs->pos.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->objs->pos.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->objs->pos.z = ft_atof(secure_atof(ptr->str + 2));
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

int		build_rot(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_rot");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->objs->rot.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->objs->rot.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->objs->rot.z = ft_atof(secure_atof(ptr->str + 2));
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

int		build_color(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_color");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		e->objs->color.x = (int)ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		e->objs->color.y = (int)ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		e->objs->color.z = (int)ft_atof(secure_atof(ptr->str + 2));
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

/*
** build_param 1er check: ne start pas par "- " ou n'est que "- "
*/

int		build_param(t_env *e, t_str *ptr)
{
	ft_putendl("- - - build_param");
	char		*sep;

	if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)) == NULL || sep[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	e->objs->param = ft_atof(secure_atof(sep + 2));
	return (-1);
}
