#include <rtv1.h>

static void		adjust_spheres(t_sphere *ptr)
{
	while (ptr)
	{
		ptr->color.x = (ptr->color.x > COLOR_MAX) ? COLOR_MAX : ptr->color.x;
		ptr->color.y = (ptr->color.y > COLOR_MAX) ? COLOR_MAX : ptr->color.y;
		ptr->color.z = (ptr->color.z > COLOR_MAX) ? COLOR_MAX : ptr->color.z;
		ptr = ptr->next;
	}
}

static void		adjust_cylinders(t_cylinder *ptr)
{
	while (ptr)
	{
		ptr->color.x = (ptr->color.x > COLOR_MAX) ? COLOR_MAX : ptr->color.x;
		ptr->color.y = (ptr->color.y > COLOR_MAX) ? COLOR_MAX : ptr->color.y;
		ptr->color.z = (ptr->color.z > COLOR_MAX) ? COLOR_MAX : ptr->color.z;
		ptr = ptr->next;
	}
}

static void		adjust_cones(t_cone *ptr)
{
	while (ptr)
	{
		ptr->color.x = (ptr->color.x > COLOR_MAX) ? COLOR_MAX : ptr->color.x;
		ptr->color.y = (ptr->color.y > COLOR_MAX) ? COLOR_MAX : ptr->color.y;
		ptr->color.z = (ptr->color.z > COLOR_MAX) ? COLOR_MAX : ptr->color.z;
		ptr = ptr->next;
	}
}

static void		adjust_plans(t_plan *ptr)
{
	while (ptr)
	{
		ptr->color.x = (ptr->color.x > COLOR_MAX) ? COLOR_MAX : ptr->color.x;
		ptr->color.y = (ptr->color.y > COLOR_MAX) ? COLOR_MAX : ptr->color.y;
		ptr->color.z = (ptr->color.z > COLOR_MAX) ? COLOR_MAX : ptr->color.z;
		ptr = ptr->next;
	}
}

void			adjust_objects(t_env *e)
{
	t_light	*ptr;

	adjust_spheres(e->spheres);
	adjust_cylinders(e->cylinders);
	adjust_cones(e->cones);
	adjust_plans(e->plans);
	if (ft_strlen(e->sdl->title) > TITLE_MAX_LEN)
		ft_strcpy(e->sdl->title + TITLE_MAX_LEN - ft_strlen(TITLE_TRUNC), \
		TITLE_TRUNC);
	e->sdl->win_x = (e->sdl->win_x > MAX_WIN_X) ? MAX_WIN_X : e->sdl->win_x;
	e->sdl->win_y = (e->sdl->win_y > MAX_WIN_Y) ? MAX_WIN_Y : e->sdl->win_y;
	e->sdl->win_x = (e->sdl->win_x < MIN_WIN_X) ? MIN_WIN_X : e->sdl->win_x;
	e->sdl->win_y = (e->sdl->win_y < MIN_WIN_Y) ? MIN_WIN_Y : e->sdl->win_y;
	e->amblight = (e->amblight > (float)1) ? 1.000 : e->amblight;
	e->amblight = (e->amblight < (float)0) ? 0.000 : e->amblight;
	ptr = e->lights;
	while (ptr)
	{
		ptr->intensity = (ptr->intensity > (float)1) ? 1.000 : ptr->intensity;
		ptr->intensity = (ptr->intensity < (float)0) ? 0.000 : ptr->intensity;
		ptr = ptr->next;
	}
}
