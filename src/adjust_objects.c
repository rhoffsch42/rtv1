#include <rtv1.h>

static void		adjust(t_obj *objs, t_light *li)
{
	while (objs)
	{
		objs->color.x = (objs->color.x > COLOR_MAX) ? COLOR_MAX : objs->color.x;
		objs->color.y = (objs->color.y > COLOR_MAX) ? COLOR_MAX : objs->color.y;
		objs->color.z = (objs->color.z > COLOR_MAX) ? COLOR_MAX : objs->color.z;
		objs->color.x = (objs->color.x < 0) ? 0 : objs->color.x;
		objs->color.y = (objs->color.y < 0) ? 0 : objs->color.y;
		objs->color.z = (objs->color.z < 0) ? 0 : objs->color.z;
		objs->param = (objs->param < 0.000f) ? 0.000f : objs->param;
		objs = objs->next;
	}
	while (li)
	{
		li->intensity = (li->intensity > (float)1) ? 1.000 : li->intensity;
		li->intensity = (li->intensity < (float)0) ? 0.000 : li->intensity;
		li = li->next;
	}
}

void			adjust_objects(t_env *e)
{

	adjust(e->objs, e->lights);
	if (ft_strlen(e->sdl->title) > TITLE_MAX_LEN)
		ft_strcpy(e->sdl->title + TITLE_MAX_LEN - ft_strlen(TITLE_TRUNC), \
		TITLE_TRUNC);
	e->sdl->size.x = (e->sdl->size.x > MAX_WIN_X) ? MAX_WIN_X : e->sdl->size.x;
	e->sdl->size.y = (e->sdl->size.y > MAX_WIN_Y) ? MAX_WIN_Y : e->sdl->size.y;
	e->sdl->size.x = (e->sdl->size.x < MIN_WIN_X) ? MIN_WIN_X : e->sdl->size.x;
	e->sdl->size.y = (e->sdl->size.y < MIN_WIN_Y) ? MIN_WIN_Y : e->sdl->size.y;
	e->sdl->mid.x = e->sdl->size.x / 2;
	e->sdl->mid.y = e->sdl->size.y / 2;
	e->amblight = (e->amblight > (float)1) ? 1.000 : e->amblight;
	e->amblight = (e->amblight < (float)0) ? 0.000 : e->amblight;
}
