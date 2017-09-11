#include <rtv1.h>

float	ft_fmodulo(float n, float mod)
{
	while (n >= mod)
		n -= mod;
	return (n);
}

float	ft_degree_scale(float degree)
{
	if (degree > 0.0)
		degree = ft_fmodulo(degree, 360.0);
	else if (degree < 0.0)
	{
		while (degree <= -360.0)
			degree += 360.0;
		if (degree < 0.0)
			degree = 360.00000 + degree;
	}
	return (degree);
}

int		color_coef(int val, float coef)
{
	if (val < 0)
		val += 255;
	return ((int)((float)val * coef));
}
