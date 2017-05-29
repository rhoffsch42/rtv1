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

t_env	*init_env(void)
{
	t_env		*e;

	if ((e = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ft_bzero((void*)e, sizeof(t_env));
	if ((e->sdl = (t_sdl*)malloc(sizeof(t_sdl))) == NULL)
		ft_errexit("Error: malloc\n", RED, MALLOC_FAIL);
	ft_bzero((void*)e->sdl, sizeof(t_sdl));
	e->sdl->win_x = DEF_WIN_Y;
	e->sdl->win_y = DEF_WIN_Y;
	e->sdl->title = ft_strdup(DEF_WIN_TITLE);
	// e->sdl->win = NULL;
	// e->sdl->surface = NULL;
	e->lights = NULL;
	e->spheres = NULL;
	e->cones = NULL;
	e->cylinders = NULL;
	e->plans = NULL;
	return (e);
}
/*
void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_errexit(SDL_GetError(), RED, SDL_FAIL);
	ft_putendl(sdl->title);
	sdl->win = SDL_CreateWindow(sdl->title, SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, sdl->win_x, sdl->win_y, SDL_WINDOW_RESIZABLE);
	SDL_ShowWindow(sdl->win);
	SDL_RaiseWindow(sdl->win);
	sdl->surface = SDL_GetWindowSurface(sdl->win);
	SDL_FillRect(sdl->surface, NULL, 0x000000);
	SDL_UpdateWindowSurface(sdl->win);
	// SDL_Delay(5000);
}
*/
