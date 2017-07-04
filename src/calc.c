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

float	power(float value, int power)
{
	while (power > 1)
	{
		value *= value;
		power--;
	}
	return (value);
}
