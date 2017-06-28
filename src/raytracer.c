#include <rtv1.h>

typedef struct	s_ray
{
	t_vector3	origin;
	t_vector3	dir;
}				t_ray;

float		intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vector3	dist;
	float		a;
	float		b;
	float		c;
	float		delta;
	float		sqrtdelta;
	float		res1;
	float		res2;

	dist = substract_vector3(&(ray->origin), &(sphere->pos));
	a = scalar_vector3(&(ray->dir), &(ray->dir));
	b = 2 * scalar_vector3(&(ray->dir), &dist);
 	c = scalar_vector3(&dist, &dist) - (sphere->r * sphere->r);
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	else
	{
		sqrtdelta = sqrtf(delta);
		res1 = (-b + sqrtdelta) / 2;
		res2 = (-b - sqrtdelta) / 2;
		if (res1 > res2)
			res1 = res2;
		printf("%f\n", res1);
		return (res1);
	}
}

void	raytracer(t_env *e)
{
	ft_putendl("- - - - - raytracer");
	int		x;
	int		y;

	y = 0;
	while (y < e->sdl->win_y)
	{
		x = 0;
		while (x < e->sdl->win_x)
		{
			if (intersect_sphere(&((t_ray){{x, y, 0}, {0, 0, 1}}), e->spheres) > 0.0001f)
				sdl_putpixel(e->sdl->surface, x, y, RGB(125, 15, 150));
			x++;
		}
		y++;
	}
	SDL_UpdateWindowSurface(e->sdl->win);
	ft_putendl("_______________________________________________________END");
}
// sdl_putpixel(e->sdl->surface, x, y, RGB(125, 15, 150));

// 1 - lancer un rayon en x y
// 2 - trouver les objets intersectes
// 3 - prendre le plus proche de la camera
// 4 - dessiner sa couleur en fonction de la lumiere
//		- ombre/brillance
