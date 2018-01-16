#include <rtv1.h>

typedef struct	s_inter_plan
{
	float		a;
	float		b;
	float		c;
	float		d;
	float		t;
	t_vector3	pr;
}				t_inter_plan;


void		intersect_cylinder(t_ray *ray, t_obj *obj)
{
	// ft_putchar_fd('.', 2);
	t_inter_plan	s;
	t_vector3		u = {0, 0, 10};
	float			root;
	float			res1;
	float			res2;

	u = vector3_rot(u, dtor_vector3(obj->rot), ROT_WAY);
	s.a = pow(ray->dir.x, 2) + pow(ray->dir.y, 2);
	s.b = 2 * ray->origin.x * ray->dir.x + 2 * ray->origin.y * ray->dir.y;
	s.c = pow(ray->origin.x, 2) + pow(ray->origin.y, 2) - obj->param;
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

void		intersect_cone(t_ray *ray, t_obj *obj)
{
	(void)ray;
	(void)obj;
}

void		intersect_plan(t_ray *ray, t_obj *obj)
{
	t_inter_plan	s;
	// ces vecteurs sont a determiner juste apres le parsing
	t_vector3		u = {0, 0, 10};// si ca passe pas a la norme,
	t_vector3		v = {10, 0, 0};// les mettre en static dans t_inter_plan
	// pour ne pas avoir a faire ces 2 rotations a chaque lance de rayon
	u = vector3_rot(u, dtor_vector3(obj->rot), ROT_WAY);
	v = vector3_rot(v, dtor_vector3(obj->rot), ROT_WAY);

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
	if (s.t < 0.0f)// || s.t > 10000.0f)
		obj->distance = 0;
	else
	{
		obj->distance = sqrt(pow(s.pr.x - ray->origin.x, 2) \
		+ pow(s.pr.y - ray->origin.y, 2) + pow(s.pr.z - ray->origin.z, 2));
	}
}

void		intersect_plan2(t_ray *ray, t_obj *obj)
{
	//faire un check si le rayon est paralele au plan et dans le plan ? de preference oui
	t_ray			raycpy;

	raycpy.origin = vector3_sub(ray->origin, obj->pos);
	//remarque: si ray.origine.y < 0, alors on regarde la face du bas/de derriere
	// peut etre utile pour ne pas dessiner la face selon le cote touche

	raycpy.origin = vector3_rot(raycpy.origin, dtor_vector3(obj->rot), -ROT_WAY);
	raycpy.dir = vector3_rot(ray->dir, dtor_vector3(obj->rot), -ROT_WAY);
	// ATTENTION: cela fonctionne que s'il n y a qu une seule rotation a faire
	// faire la fonction de matrice de rotation inverse droit: ZYX

	// trouver l'intersection ray plan. => sur y = 0
	// ray->origin + T * ray->dir = M(x, 0, z)
	// ray->origin.y + T * ray->dir.y = 0
	// T * ray->dir.y = - ray->origin.y
	// T = -(raycpy.origin.y) / raycpy.dir.y
	obj->distance = -(raycpy.origin.y) / raycpy.dir.y;
	// if (obj->distance < 0.000000f)
		// obj->distance *= -1;

	//////////////////////////////////////////////////////////// resultat identique
	t_vector3	n = {0, 1, 0};
	t_vector3	q = {0, 0, 1};
	t_vector3	subs = substract_vector3(&q, &(raycpy.origin));
	float a = scalar_vector3(&n, &subs);
	float b = scalar_vector3(&n, &(raycpy.dir));
	float t = a / b;
	obj->distance = t;

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
	static int c = 0; c++;
	t_obj	*closest;

	closest = NULL;
	while (ptr)
	{
		if (c == 1 && ptr->type == 3)
			printf("plan:\t%f\ttype%d\n", ptr->distance, ptr->type);
		if (ptr->distance > draw_dist)
			if (!closest || (ptr->distance < closest->distance))
				closest = ptr;
		ptr = ptr->next;
	}
	// if (closest)
		// printf("clo:\t%f\ttype%d\n", closest->distance, closest->type);
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
	void		(*intersect[4])(t_ray*, t_obj*) = \
		{intersect_sphere, intersect_cylinder, intersect_cone, intersect_plan2};
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
			ray2.dir = vector3_rot(ray.dir, (t_vector3){DTOR(x_pitched), DTOR(y_pitched), DTOR(0)}, ROT_LEFT);
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
						col.x = 22;
						col.y = 22;
						col.z = 22;
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
	printf("_______________________________________________________END\n");
}

// 1 - lancer un rayon en x y
// 2 - trouver les objets intersectes
// 3 - prendre le plus proche de la camera
// 4 - dessiner sa couleur en fonction de la lumiere
//		- ombre/brillance
