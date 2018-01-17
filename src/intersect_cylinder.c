#include <rtv1.h>

void		intersect_cylinder(t_ray ray, t_obj *obj)
{
	// ft_putchar_fd('.', 2);
	t_inter_plan	s;
	t_vector3		u = {0, 0, 10};
	float			root;
	float			res1;
	float			res2;

	u = vector3_rot(u, dtor_vector3(obj->rot), ROT_WAY);
	s.a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2);
	s.b = 2 * ray.origin.x * ray.dir.x + 2 * ray.origin.y * ray.dir.y;
	s.c = pow(ray.origin.x, 2) + pow(ray.origin.y, 2) - obj->param;
	s.t = s.b * s.b - 4 * s.a * s.c;
	if (s.t < 0.000f)
		obj->distance = -1.0f;
	else
	{
		root = sqrtf(s.t);
		res1 = (-s.b + root) / (2 * s.a);
		res2 = (-s.b - root) / (2 * s.a);
		if (res1 > res2)
			res1 = res2;
		obj->distance = res1;
	}
	/////////////////////////////////
	// a, b, c, r, connus
	// x2 + y2 + z2 - (ax + by +cz)2 / (a2 + b2 + c2) = r2
	// // equation parametrique (u? v?)
	// x = r * cos(u)
	// y = r * sin(u)
	// z = v
	// // ou
	// x = r * cos(u - v)
	// y = r * sin(u - v)
	// z = u + v
	/////////////////////////////////
}
