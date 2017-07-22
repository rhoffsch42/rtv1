#include <rtv1.h>

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

t_vector3	dtor_vector3(t_vector3 src)
{
	return ((t_vector3){DTOR(src.x), DTOR(src.y), DTOR(src.z)});
}

typedef struct	s_inter_plan
{
	float		a;
	float		b;
	float		c;
	float		d;
	float		t;
	t_vector3	pr;

}				t_inter_plan;

void		intersect_plan(t_ray *ray, t_obj *obj)
{
	t_inter_plan	s;
	t_vector3		u = {0, 0, 10};// si ca passe pas a la norme,
	t_vector3		v = {10, 0, 0};// les mettre en static dans t_inter_plan

	rot_vector33(&u, &u, dtor_vector3(obj->rot), ROT_WAY);
	rot_vector33(&v, &v, dtor_vector3(obj->rot), ROT_WAY);
	// float	a, b, c;// produit vectoriel u/\v
	s.a = u.y * v.z - u.z * v.y;
	s.b = u.z * v.x - u.x * v.z;
	s.c = u.x * v.y - u.y * v.x;
	// float	d; //equation cartesienne
	s.d = -(s.a * obj->pos.x + s.b * obj->pos.y + s.c * obj->pos.z);
	// float t = 0;// t = inconnu
	// t_vector3	pr; // equations parametriques de la droite/ray (points de la droite/ray)
	s.t = -(s.d + s.a * ray->origin.x + s.b * ray->origin.y + s.c \
	* ray->origin.z) / (s.a * ray->dir.x + s.b * ray->dir.y + s.c * ray->dir.z);
	s.pr.x = ray->origin.x + ray->dir.x * s.t;
	s.pr.y = ray->origin.y + ray->dir.y * s.t;
	s.pr.z = ray->origin.z + ray->dir.z * s.t;
	if (s.t < 0.0f || s.t > 10000.0f)
		obj->distance = 0;
	else
	{
		obj->distance = sqrt(pow(s.pr.x - ray->origin.x, 2) \
		+ pow(s.pr.y - ray->origin.y, 2) + pow(s.pr.z - ray->origin.z, 2));
	}
}

void		intersect_sphere(t_ray *ray, t_obj *obj)
{
	t_vector3	center;
	float		a;
	float		b;
	float		c;
	float		delta;
	float		sqrtdelta;
	float		res1;
	float		res2;

	center = substract_vector3(&(ray->origin), &(obj->pos));
	a = scalar_vector3(&(ray->dir), &(ray->dir));
	b = 2 * scalar_vector3(&(ray->dir), &center);
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
			y_pitched = (x - e->sdl->mid.x) * pitch;
			// y_pitched = y_pitched * cosf(DTOR(y_pitched));
			// printf("%f\t%f\n", x_pitched, y_pitched);
			// printf("\t(%f\t%f)\n", x_pitched * cosf(DTOR(x_pitched)), y_pitched * cosf(DTOR(y_pitched)));
			rot_vector3(&(ray.dir), &(ray2.dir), (t_vector3){DTOR(x_pitched), DTOR(y_pitched), DTOR(0)}, ROT_LEFT);
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
					if (x == 385 && y == 385 && obj->type == SPHERE)
						debug_ray(obj, ray2, col);
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
