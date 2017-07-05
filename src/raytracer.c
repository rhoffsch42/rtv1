#include <rtv1.h>

typedef struct	s_ray
{
	t_vector3	origin;
	t_vector3	dir;
}				t_ray;

void		intersect_cylinder(t_ray *ray, t_obj *obj)
{
	(void)ray;
	(void)obj;
}

void		intersect_cone(t_ray *ray, t_obj *obj)
{
	(void)ray;
	(void)obj;
}

void	print_vector3f(t_vector3 vector)
{
	printf("x %f\n", vector.x);
	printf("y %f\n", vector.y);
	printf("z %f\n", vector.z);
}

t_vector3	dtor_vector3(t_vector3 src)
{
	return ((t_vector3){DTOR(src.x), DTOR(src.y), DTOR(src.z)});
}

void		intersect_plan(t_ray *ray, t_obj *obj)
{
	// ax + by + cz + d = 0;
	// t_vector3	cp;
	// t_vector3	p1;
	// t_vector3	p2;
	//
	// cp.x = obj.x - ray->origin.x;
	// cp.x = obj.y - ray->origin.y;
	// cp.x = obj.z - ray->origin.z;
	// p1.x = ;
	// p1.y = ;
	// p1.z = ;
	// p2.x = ;
	// p2.x = ;
	// p2.x = ;
	//
	//
	// CP + a*P1 + b*P2 - cR = 0
	// aP1 + bP2 - cR + CP = 0;


/*	//////////////////////////////// definition du plan P(o, u->, v->)
	t_vector3	p = obj->pos;
	t_vector3	u = {100, 0, 0};
	t_vector3	v = {0, 0, 100};
	obj->rot.x = 0.0f;
	obj->rot.y = 90.0f;
	obj->rot.z = 0.0f;

	// print_vector3f(x);ENDL
	// print_vector3f(z);ENDL
	rot_vector3(&u, &u, dtor_vector3(obj->rot), ROT_WAY);
	rot_vector3(&v, &v, dtor_vector3(obj->rot), ROT_WAY);
	// print_vector3f(x);ENDL
	// print_vector3f(z);ENDL


	t_vector3	pp; // equations parametriques du plan (points du plan)
	pp.x = plan.x + A * u.x + B * v.x;
	pp.y = plan.y + A * u.y + B * v.y;
	pp.z = plan.z + A * u.z + B * v.z;

	float	a, b, c, d, equation_plan; //equation cartesienne
	a = u.y * v.z - u.z * v.y;
	b = u.z * v.x - u.x * v.z;
	c = u.x * v.y - u.y * v.x;
	d = -(a * p.x + b * p.y + c * p.z);
	equation_plan = a * pp.x + b * pp.y + c * pp.z + d;

	t_vector3	pr; // equations parametriques de la droite/ray (points de la droite/ray)
	pr.x = ray.origin.x ray.dir.x * T;
	pr.y = ray.origin.y ray.dir.y * T;
	pr.z = ray.origin.z ray.dir.z * T;

	exit(0);
*/	/////////////////////////////////
	(void)ray;
	(void)obj;
}

void		intersect_sphere(t_ray *ray, t_obj *obj)
{
	t_vector3	dist;
	float		a;
	float		b;
	float		c;
	float		delta;
	float		sqrtdelta;
	float		res1;
	float		res2;

	dist = substract_vector3(&(ray->origin), &(obj->pos));
	a = scalar_vector3(&(ray->dir), &(ray->dir));
	b = 2 * scalar_vector3(&(ray->dir), &dist);
 	c = scalar_vector3(&dist, &dist) - (obj->param * obj->param);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		obj->distance = -1.0f;
	else
	{
		sqrtdelta = sqrtf(delta);
		res1 = (-b + sqrtdelta) / 2;
		res2 = (-b - sqrtdelta) / 2;
		if (res1 > res2)
			res1 = res2;
		// printf("%f\n", res1);
		obj->distance = res2;
	}
}

t_obj	*get_closest_object(t_obj *ptr, float draw_dist)
{
	t_obj	*closest;

	closest = NULL;
	while (ptr)
	{
		if (ptr->distance > draw_dist)
			if (!closest || (ptr->distance < closest->distance))
				closest = ptr;
		ptr = ptr->next;
	}
	return (closest);
}

void	raytracer(t_env *e)
{
	ft_putendl("- - - - - raytracer");
	t_obj		*ptr;
	float		x;
	float		y;
	int			len[2];
	t_obj		*obj;
	void		(*intersect[4])(t_ray*, t_obj*) = {intersect_sphere, intersect_cylinder, intersect_cone, intersect_plan};
	t_ray		ray;
	t_ray		ray2;
	float		pitch = FOV / e->sdl->size.x;
	float		x_pitched;
	float		y_pitched;

	ray.origin = e->cam.pos;
	ray.dir.y = 0;
	ray.dir.x = 0;
	ray.dir.z = SCREEN_DIST;
	ray2.origin = e->cam.pos;
	ray2.dir.y = 0;
	ray2.dir.x = 0;
	ray2.dir.z = SCREEN_DIST;
	y = 0;
	while (y < e->sdl->size.y)
	{
		x = 0;
		x_pitched = (y - e->sdl->mid.y) * pitch;
		// x_pitched = x_pitched * cosf(DTOR(x_pitched));
		while (x < e->sdl->size.x)
		{
			ptr = e->objs;
			obj = NULL;
			len[0] = -1;
			if (0)
			{
				ray.dir.y = y - e->sdl->mid.y - e->cam.pos.y;
				ray.dir.x = x - e->sdl->mid.x - e->cam.pos.x;
				ray.dir.z = SCREEN_DIST;
				rot_vector33(&(ray.dir), &(ray2.dir), (t_vector3){DTOR(0), DTOR(0), DTOR(0)}, ROT_WAY);
			} else {
				y_pitched = (x - e->sdl->mid.x) * pitch;
				// y_pitched = y_pitched * cosf(DTOR(y_pitched));
				// printf("%f\t%f\n", x_pitched, y_pitched);
				// printf("\t(%f\t%f)\n", x_pitched * cosf(DTOR(x_pitched)), y_pitched * cosf(DTOR(y_pitched)));
				rot_vector33(&(ray.dir), &(ray2.dir), (t_vector3){DTOR(x_pitched), DTOR(y_pitched), DTOR(0)}, ROT_WAY);
			}
			while (ptr)
			{
				intersect[ptr->type](&ray2, ptr);
				ptr = ptr->next;
			}
			if ((obj = get_closest_object(e->objs, DRAW_DIST)))
				sdl_putpixel(e->sdl->surface, x, y, RGB(obj->color.x, obj->color.y, obj->color.z));
			x++;
		}
		y++;
	}
	SDL_UpdateWindowSurface(e->sdl->win);
	ft_putendl("_______________________________________________________END");
}

// 1 - lancer un rayon en x y
// 2 - trouver les objets intersectes
// 3 - prendre le plus proche de la camera
// 4 - dessiner sa couleur en fonction de la lumiere
//		- ombre/brillance
