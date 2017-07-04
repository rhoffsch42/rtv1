#include <rtv1.h>

typedef struct	s_ray
{
	t_vector3	origin;
	t_vector3	dir;
}				t_ray;

float		intersect_cylinder(t_ray *ray, t_obj *obj)
{
	(void)ray;
	(void)obj;
	return (-1);
}

float		intersect_cone(t_ray *ray, t_obj *obj)
{
	(void)ray;
	(void)obj;
	return (-1);
}

float		intersect_plan(t_ray *ray, t_obj *obj)
{
	(void)ray;
	(void)obj;
	return (-1);
}

float		intersect_sphere(t_ray *ray, t_obj *obj)
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
		return (-1);
	else
	{
		sqrtdelta = sqrtf(delta);
		res1 = (-b + sqrtdelta) / 2;
		res2 = (-b - sqrtdelta) / 2;
		if (res1 > res2)
			res1 = res2;
		// printf("%f\n", res1);
		return (res1);
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
	float		(*intersect[4])(t_ray*, t_obj*) = {intersect_sphere, intersect_cylinder, intersect_cone, intersect_plan};
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
		// x_pitched *= cosf(DTOR(x_pitched));
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
				rot_vector3(&(ray.dir), &(ray2.dir), (t_vector3){DTOR(0), DTOR(0), DTOR(0)}, ROT_WAY);
			} else {
				y_pitched = (x - e->sdl->mid.x) * pitch;
				// y_pitched *= cosf((y_pitched));
				// printf("%f\t%f\n", y_pitched, x_pitched);
				rot_vector33(&(ray.dir), &(ray2.dir), (t_vector3){DTOR(x_pitched), DTOR(y_pitched), DTOR(0)}, ROT_WAY);
			}
			while (ptr)
			{
				if (obj == NULL || len[0] == -1)
				{
					obj = ptr;
					len[0] = intersect[ptr->type](&ray2, ptr);
				}
				else
				{
					len[1] = intersect[ptr->type](&ray2, ptr);
					if (len[1] != -1 && len[1] <= len[0])
					{
						obj = ptr;
						len[0] = len[1];
					}
				}
				ptr = ptr->next;
			}
			if (len[0] > DRAW_DIST)
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
