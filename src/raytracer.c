#include <rtv1.h>

t_ray	transpose_ray(t_ray ray, t_obj obj)
{
	t_ray			raycpy;

	raycpy.origin = vector3_sub(ray.origin, obj.pos);
	//remarque: si ray.origine.y < 0, alors on regarde la face du bas/de derriere
	// peut etre utile pour ne pas dessiner la face selon le cote touche

	raycpy.origin = vector3_rot(raycpy.origin, dtor_vector3(obj.rot), -ROT_WAY);
	raycpy.dir = vector3_rot(ray.dir, dtor_vector3(obj.rot), -ROT_WAY);
	// ATTENTION: cela fonctionne que s'il n y a qu une seule rotation a faire
	// ou pas ?
	// faire la fonction de matrice de rotation inverse droit: ZYX
	return (raycpy);
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
	void		(*intersect[4])(t_ray, t_obj*) = \
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
		// x_pitched *= cosf(DTOR(x_pitched));
		while (x < e->sdl->size.x)
		{
			ptr = e->objs;
			obj = NULL;
			y_pitched = (x - e->sdl->mid.x) * pitch;
			// y_pitched *= cosf(DTOR(y_pitched));
			// printf("%f\t%f\n", x_pitched, y_pitched);
			// printf("\t(%f\t%f)\n", x_pitched * cosf(DTOR(x_pitched)), y_pitched * cosf(DTOR(y_pitched)));
			ray2.dir = vector3_rot(ray.dir, (t_vector3){DTOR(x_pitched), DTOR(y_pitched), DTOR(0)}, ROT_LEFT);
			reset_distances(ptr);
			while (ptr)
			{
				intersect[ptr->type](ray2, ptr);
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
