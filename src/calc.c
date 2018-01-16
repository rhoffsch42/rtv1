#include <rtv1.h>

t_vector3	substract_vector3(t_vector3 *v1, t_vector3 *v2)
{
	// ft_putchar('-');ENDL
	// ft_putnbr(v1->x);ENDL
	// ft_putnbr(v1->y);ENDL
	// ft_putnbr(v1->z);ENDL
	// ft_putnbr(v2->x);ENDL
	// ft_putnbr(v2->y);ENDL
	// ft_putnbr(v2->z);ENDL
	return ((t_vector3){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z });
}

float		scalar_vector3(t_vector3 *v1, t_vector3 *v2)
{
	// ft_putchar('.');ENDL
	// ft_putnbr(v1->x);ENDL
	// ft_putnbr(v1->y);ENDL
	// ft_putnbr(v1->z);ENDL
	// ft_putnbr(v2->x);ENDL
	// ft_putnbr(v2->y);ENDL
	// ft_putnbr(v2->z);ENDL
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector3	dtor_vector3(t_vector3 src)
{
	return ((t_vector3){DTOR(src.x), DTOR(src.y), DTOR(src.z)});
}


void	translate_vector3(t_vector3 *dst, t_vector3 *src, t_vector3 *vec, float coef)
{
	dst->x = src->x + vec->x * coef;
	dst->y = src->y + vec->y * coef;
	dst->z = src->z + vec->z * coef;
}
