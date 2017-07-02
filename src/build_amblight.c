#include <rtv1.h>

t_str	*build_amblight(t_env *e, t_str *ptr, int id)
{
	ft_putendl("- - - - - -build_amblight");
	(void)id;
	char	*sep;

	sep = ptr->str + ft_strlen(YA_AMBLIGHT) + 1;
	if (sep[0] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	sep++;
	e->amblight = ft_atof(secure_atof(sep));
	return (ptr);
}
