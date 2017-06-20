/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:26:23 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/25 17:26:25 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	init_yaml_chart(t_env *e)
{
	e->chart[0] = (t_chart){YA_WIN, \
		2, YA_CHAR, Y_TITLE | Y_SIZE, (void*)build_win};
	e->chart[1] = (t_chart){YA_AMBLIGHT, 1, YA_FLOAT, 0, (void*)build_amblight};
	e->chart[2] = (t_chart){YA_CAM, \
		3, YA_CHAR, Y_POS | Y_ROT | Y_STEP, (void*)build_cam};
	e->chart[3] = (t_chart){YA_LIGHT, \
		3, YA_CHAR, Y_POS | Y_ROT | Y_INTENSITY, (void*)build_light};
	e->chart[4] = (t_chart){YA_CONE, \
		4, YA_CHAR, Y_POS | Y_ROT | Y_COLOR | Y_ANGLE, (void*)build_cone};
	e->chart[5] = (t_chart){YA_PLAN, \
		3, YA_CHAR, Y_POS | Y_ROT | Y_COLOR, (void*)build_plan};
	e->chart[6] = (t_chart){YA_SPHERE, \
		4, YA_CHAR, Y_POS | Y_ROT | Y_COLOR | Y_RAY, (void*)build_sphere};
	e->chart[7] = (t_chart){YA_CYLINDER, \
		4, YA_CHAR, Y_POS | Y_ROT | Y_COLOR | Y_RAY, (void*)build_cylinder};
	e->chart[8] = (t_chart){YA_TITLE, 1, YA_CHAR, 0, (void*)build_win};
	e->chart[9] = (t_chart){YA_SIZE, 2, YA_FLOAT, 0, (void*)build_win};
	e->chart[10] = (t_chart){YA_POS, 3, YA_FLOAT, 0, (void*)build_win};
	e->chart[11] = (t_chart){YA_ROT, 3, YA_FLOAT, 0, (void*)build_win};
	e->chart[12] = (t_chart){YA_STEP, 2, YA_FLOAT, 0, (void*)build_win};
	e->chart[13] = (t_chart){YA_INTENSITY, 1, YA_FLOAT, 0, (void*)build_win};
	e->chart[14] = (t_chart){YA_COLOR, 3, YA_FLOAT, 0, (void*)build_win};
	e->chart[15] = (t_chart){YA_ANGLE, 1, YA_FLOAT, 0, (void*)build_win};
	e->chart[16] = (t_chart){YA_RAY, 1, YA_FLOAT, 0, (void*)build_win};
}

t_env	*init_env(void)
{
	t_env		*e;

	if ((e = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ft_bzero((void*)e, sizeof(t_env));
	if ((e->sdl = (t_sdl*)malloc(sizeof(t_sdl))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ft_bzero((void*)e->sdl, sizeof(t_sdl));
	e->sdl->win_x = DEF_WIN_X;
	e->sdl->win_y = DEF_WIN_Y;
	e->sdl->title = ft_strdup(DEF_WIN_TITLE);
	e->sdl->surface = NULL;
	e->sdl->win = NULL;
	ft_bzero(&e->cam, sizeof(t_cam));
	e->amblight = 1;
	e->lights = NULL;
	e->spheres = NULL;
	e->cones = NULL;
	e->cylinders = NULL;
	e->plans = NULL;
	init_yaml_chart(e);
	return (e);
}

void	init_sdl(t_sdl *sdl)
{
	(void)sdl;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_errexit(SDL_GetError(), RED, SDL_FAIL);
	sdl->win = SDL_CreateWindow(sdl->title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, sdl->win_x, sdl->win_y, SDL_WINDOW_RESIZABLE);
	SDL_ShowWindow(sdl->win);
	SDL_RaiseWindow(sdl->win);
	sdl->surface = SDL_GetWindowSurface(sdl->win);
	SDL_FillRect(sdl->surface, NULL, 0x000000);
	SDL_UpdateWindowSurface(sdl->win);
	SDL_Delay(5000);
}
