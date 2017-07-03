#include <rtv1.h>

void	rot_vector2(t_vector2 *src, t_vector2 *dst, float rad, float rot_direction)
{
	float	x;
	float	y;

	x = src->x;
	y = src->y;
	dst->x = x * cosf(rad * rot_direction) - y * sinf(rad * rot_direction);
	dst->y = x * sinf(rad * rot_direction) + y * cosf(rad * rot_direction);
}

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
