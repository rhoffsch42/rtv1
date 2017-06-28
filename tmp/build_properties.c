#include <rtv1.h>

/* build_pos
** 1er check: ne start pas par "- " ou n'est que "- "
*/

int		fill_vector(char *src, void *ptr, int size)
{
	ft_putendl("- - - fill_vector");
	static char		o = 0;

	if (ft_strlen(src) < 3 || src[0] != '-' || src[1] != ' ')
		error_yaml(src, YA_ERROR);
	if (o == 0)
		((t_vector3*)ptr)->pos.x = ft_atof(secure_atof(src + 2));
	else if (o == 1)
		((t_vector3*)ptr)->pos.y = ft_atof(secure_atof(src + 2));
	else if (o == 2)
		((t_vector3*)ptr)->pos.z = ft_atof(secure_atof(src + 2));
	else
		error_yaml(src, YA_ERROR);
	o++;
	if (o == size)
	{
		o = 0;
		return (-1);
	}
	return (0);
}

int		build_pos1(t_env *e, t_str *ptr, t_sphere *obj)
{
	ft_putendl("- - - build_pos");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		obj->pos.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		obj->pos.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		obj->pos.z = ft_atof(secure_atof(ptr->str + 2));
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

int		build_rot1(t_env *e, t_str *ptr, t_sphere *obj)
{
	ft_putendl("- - - build_rot");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		obj->rot.x = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		obj->rot.y = ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		obj->rot.z = ft_atof(secure_atof(ptr->str + 2));
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

int		build_color1(t_env *e, t_str *ptr, , t_sphere *obj)
{
	ft_putendl("- - - build_color");
	static char		o = 0;

	if (ft_strlen(ptr->str) < 3 || ptr->str[0] != '-' || ptr->str[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	if (o == 0)
		obj->color.x = (int)ft_atof(secure_atof(ptr->str + 2));
	else if (o == 1)
		obj->color.y = (int)ft_atof(secure_atof(ptr->str + 2));
	else if (o == 2)
		obj->color.z = (int)ft_atof(secure_atof(ptr->str + 2));
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

int		build_ray1(t_env *e, t_str *ptr, float *ray)
{
	ft_putendl("- - - build_ray");
	char		*sep;

	if ((sep = ft_strchr(ptr->str, YA_SEPARATOR)) == NULL || sep[1] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	*ray = ft_atof(secure_atof(sep + 2));
	return (-1);
}
