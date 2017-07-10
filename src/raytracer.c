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
	t_vector3	u = {0, 0, 10};
	t_vector3	v = {10, 0, 0};

	float	m, n, o;// produit vectoriel u/\v
	m = u.y * v.z - u.z * v.y;
	n = u.z * v.x - u.x * v.z;
	o = u.x * v.y - u.y * v.x;

	float	d; //equation cartesienne
	d = -(m * obj->pos.x + n * obj->pos.y + o * obj->pos.z);

	float T = 0;// T = inconnu
	t_vector3	pr; // equations parametriques de la droite/ray (points de la droite/ray)

	T = -(d + m * ray->origin.x + n * ray->origin.y + o * ray->origin.z) \
		/ (m * ray->dir.x + n * ray->dir.y + o * ray->dir.z);
	pr.x = ray->origin.x + ray->dir.x * T;
	pr.y = ray->origin.y + ray->dir.y * T;
	pr.z = ray->origin.z + ray->dir.z * T;
	if (T < 0.0f || T > 10000.0f)
		obj->distance = 0;
	else
		obj->distance = sqrt(power(pr.x - ray->origin.x, 2) \
			+ power(pr.y - ray->origin.y, 2) + power(pr.z - ray->origin.z, 2));
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
	// printf("clo:\t%f\n", closest->distance);
	return (closest);
}

void	reset_distances(t_obj *ptr)
{
	while (ptr)
	{
		ptr->distance = 0;
		ptr = ptr->next;
	}
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
			reset_distances(ptr);
			while (ptr)
			{
				intersect[ptr->type](&ray2, ptr);
				ptr = ptr->next;
			}
			if ((obj = get_closest_object(e->objs, DRAW_DIST)))
			{
				t_vector3	col = {obj->color.x, obj->color.y, obj->color.z};
				if (obj->type == PLAN || obj->type == SPHERE)
				{
					if (obj->distance > 500.0f)
					{
						col.x = 0;
						col.y = 0;
						col.z = 0;
					}
					else {
						float coef = obj->distance / 500.0f;
						col.x = (int)(obj->color.x * (1.0f - coef));
						col.y = (int)(obj->color.y * (1.0f - coef));
						col.z = (int)(obj->color.z * (1.0f - coef));
					}
					if (x == 400 && obj->type == SPHERE)
					{
						printf("%f\t%f\t%f\t%f\n", \
						obj->distance, col.x, col.y, col.z);
					}
				}
				sdl_putpixel(e->sdl->surface, x, y, \
					RGB(col.x, col.y, col.z));
			}
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
