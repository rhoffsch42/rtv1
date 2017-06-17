#include <rtv1.h>

t_str	*build_amblight(t_env *e, t_str *ptr)
{
	ft_putendl("- - - - - -build_amblight");
	char	*sep;

	sep = ptr->str + ft_strlen(YA_AMBLIGHT) + 1;
	if (sep[0] != ' ')
		error_yaml(ptr->str, YA_ERROR);
	sep++;
	e->amblight = ft_atof(sep);
	if (e->amblight > (float)1)
	{
		ft_putstr_color("Ambiant light topped at 1.0\n", MAGENTA);
		e->amblight = 1.0000;
	}
	return (ptr);
}
