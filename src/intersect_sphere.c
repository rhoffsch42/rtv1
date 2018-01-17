#include <rtv1.h>

void		intersect_sphere(t_ray ray, t_obj *obj)
{
	t_vector3	center;
	float		a;
	float		b;
	float		c;
	float		delta;
	float		sqrtdelta;
	float		res1;
	float		res2;

	center = substract_vector3(&(ray.origin), &(obj->pos));
	a = scalar_vector3(&(ray.dir), &(ray.dir));
	b = 2 * scalar_vector3(&(ray.dir), &center);
 	c = scalar_vector3(&center, &center) - (obj->param * obj->param);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		obj->distance = -1.0f;
	else
	{
		sqrtdelta = sqrtf(delta);
		res1 = (-b + sqrtdelta) / 2.0f;
		res2 = (-b - sqrtdelta) / 2.0f;
		if (res1 > res2)
			res1 = res2;
		// printf("%f\n", res1);
		obj->distance = res2;
	}
}
