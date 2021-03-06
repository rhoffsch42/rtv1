#include <rtv1.h>

void		intersect_plan(t_ray ray, t_obj *obj)
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
	s.t = -(s.d + s.a * ray.origin.x + s.b * ray.origin.y + s.c \
	* ray.origin.z) / (s.a * ray.dir.x + s.b * ray.dir.y + s.c * ray.dir.z);
	s.pr.x = ray.origin.x + ray.dir.x * s.t;
	s.pr.y = ray.origin.y + ray.dir.y * s.t;
	s.pr.z = ray.origin.z + ray.dir.z * s.t;
	if (s.t < 0.0f)// || s.t > 10000.0f)
		obj->distance = 0;
	else
	{
		obj->distance = sqrt(pow(s.pr.x - ray.origin.x, 2) \
		+ pow(s.pr.y - ray.origin.y, 2) + pow(s.pr.z - ray.origin.z, 2));
	}
}

void		intersect_plan2(t_ray ray, t_obj *obj)
{
	//faire un check si le rayon est paralele au plan et dans le plan ? de preference oui
	t_ray			raycpy;

	raycpy = transpose_ray(ray, *obj);
	// trouver l'intersection ray plan. => sur y = 0
	// ray.origin + T * ray.dir = M(x, 0, z)
	// ray.origin.y + T * ray.dir.y = 0
	// T * ray.dir.y = - ray.origin.y
	// T = -(raycpy.origin.y) / raycpy.dir.y

	// T = combien de fois on multiplie le vecteur ray (magnitude de 1) pour atteindre l'object
	// T n'est pas la distance reelle,
	// distance reelle = T * vector3_magnitude(ray)
	// si magnitude == 1, alors distance = T

	obj->distance = -(raycpy.origin.y) / raycpy.dir.y;

	// if (obj->distance < 0.000000f)
		// obj->distance *= -1;// pas utile puisqu'on test si dist > draw_dist (5) apres
	return ;
	//////////////////////////////////////////////////////////// resultat identique
	t_vector3	n = {0, 1, 0};
	t_vector3	q = {0, 0, 1};
	t_vector3	subs = vector3_sub(q, raycpy.origin);
	float a = vector3_dot(n, subs);
	float b = vector3_dot(n, raycpy.dir);
	float t = a / b;
	obj->distance = t;
}

void		intersect_plan3(t_ray ray, t_obj *obj)
{
	t_ray		raycpy;
	t_vector3	n = {0, 1, 0};
	float		dot;
	float		t;

	raycpy = transpose_ray(ray, *obj);
	dot = vector3_dot(n, raycpy.dir);
	if (dot == 0)
		return ;
	t = -vector3_dot(n, raycpy.origin) / dot;
	if (t > 0.000000f)
		obj->distance = t;
}
