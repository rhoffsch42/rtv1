#include <rtv1.h>

void		intersect_sphere(t_ray ray, t_obj *obj)
{
	t_vector3	center;
	float		a;
	float		b;
	float		c;
	float		delta;
	float		sqrtdelta;
	float		t1;
	float		t2;

	center = vector3_sub(ray.origin, obj->pos);
	a = vector3_dot(ray.dir, ray.dir);
	b = 2 * vector3_dot(ray.dir, center);
 	c = vector3_dot(center, center) - (obj->param * obj->param);
	delta = b * b - 4 * a * c;
	if (delta > 0.000000f)
	{
		sqrtdelta = sqrtf(delta);
		t1 = (-b + sqrtdelta) / (2 * a);
		t2 = (-b - sqrtdelta) / (2 * a);
		if (t1 > t2)
			t1 = t2;
		obj->distance = t1;
	}
}

/*
**	intersect_sphere2: too many operations
**	ray rotation (in transpose function) is useless since distance will be the same
*/
void		intersect_sphere2(t_ray ray, t_obj *obj)
{
	t_ray	raycpy;
	float	a;
	float	b;
	float	c;
	float	delta;
	float	sqrtdelta;
	float	t1;
	float	t2;

	raycpy = transpose_ray(ray, *obj);
	a = vector3_dot(raycpy.dir, raycpy.dir);
	b = 2.0f * vector3_dot(raycpy.dir, raycpy.origin);
	c = vector3_dot(raycpy.origin, raycpy.origin) - (obj->param * obj->param);
	delta = b * b - 4 * a * c;
	if (delta > 0.000000f)
	{
		sqrtdelta = sqrtf(delta);
		t1 = (-b + sqrtdelta) / (2.0f * a);
		t2 = (-b - sqrtdelta) / (2.0f * a);
		if (t1 > t2)
			t1 = t2;
		obj->distance = t1;
	}
}
/*
**	T = how many times we multiply ray to intersect the object
**	T isnt the real distance,
**	real_distance = T * vector3_magnitude(ray);
**	if magnitude == 1, then distance = T
**
**	when sphere is at origin
**	X² + Y² + Z² = R²
**	X = ray.origin.x + ray.dir.x * T
**	Y = ray.origin.y + ray.dir.y * T
**	Z = ray.origin.z + ray.dir.z * T
*/
