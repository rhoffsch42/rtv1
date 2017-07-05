/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:26:53 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/25 17:26:55 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	print_vector3(t_vector3	vector)
{
	printf("%d\t", (int)vector.x);
	printf("%d\t", (int)vector.y);
	printf("%d\t", (int)vector.z);
}
void	print_vector2(t_vector2	vector)
{
	printf("%d\t", (int)vector.x);
	printf("%d\t", (int)vector.y);
}

void	print_objects(t_env *e)
{
	ENDL
	ENDL
	ENDL
	printf("amblight\t%f\n", e->amblight);
	printf("window  \t%d\t%d\t%d\t%d\t\"%s\"\n", (int)e->sdl->size.x, (int)e->sdl->size.y, (int)e->sdl->mid.x, (int)e->sdl->mid.y, e->sdl->title);
	t_light	*li = e->lights;
	while (li)
	{
		printf("lights  \t");
		print_vector3(li->pos);
		print_vector3(li->rot);
		printf("%f\n", li->intensity);
		li = li->next;
	}
	t_obj	*obj = e->objs;
	char	*tab[4] = {"sphere", "cylinder", "cone", "plan"};
	while (obj)
	{
		printf("%s    \t", tab[obj->type]);
		print_vector3(obj->pos);
		print_vector3(obj->rot);
		print_vector3(obj->color);
		printf("%f\n", obj->param);
		obj = obj->next;
	}
}

int		main(int ac, char **av)
{
	// t_vector3	vec = { 100, 100, 100 };
	// t_vector3	rot = { DTOR(90), DTOR(0), DTOR(0) };
	//
	// printf("%f\t%f\t%f\n", vec.x, vec.y, vec.z);
	// rot_vector3(&vec, &vec, &rot, ROT_WAY);
	// printf("%f\t%f\t%f\n", vec.x, vec.y, vec.z);
	// exit(0);
	// sdl_test();exit(0);
	// printf("%f\n", atof("  \t -.2.4 6"));exit(0);
	// ft_putnbrendl(ft_atoi(NULL));exit(0);
	t_env	*e;

	ft_putendl("rtv1");
	e = init_env();
	get_scene(e, ac, av);
	adjust_objects(e);
	print_objects(e);
	init_sdl(e->sdl);
	SDL_Surface		*image_surface = SDL_LoadBMP("bg.bmp");
	ft_putendl((image_surface) ? "BG loaded" : "BG FUCK");
	SDL_BlitSurface(image_surface, NULL, e->sdl->surface, &((SDL_Rect){0, 0, e->sdl->size.x, e->sdl->size.y}));
	raytracer(e);

	SDL_Event	event;
	int			escape_pressed = 0;
	while (escape_pressed == 0)
	{
		while (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				escape_pressed = 1;
				break ;
			}
		}
	}
	return (OK);
}

int		sdl_test(void)
{
	SDL_Window		*sdl_win = NULL;
	int				win_x = 800;
	int				win_y = 800;
 	if (SDL_Init(SDL_INIT_VIDEO) != 0)
 	{
 		fprintf(stdout, "Échec: init de la SDL (%s)\n", SDL_GetError());
 		return (-1);
 	}
 	sdl_win = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_x, win_y, SDL_WINDOW_RESIZABLE);
 	SDL_ShowWindow(sdl_win);
 	SDL_RaiseWindow(sdl_win);
 	if (sdl_win)
 	{
 		 int i = 0;
 	// 	int i = 1;
 if (i)	{
 			SDL_Surface		*window_surface = SDL_GetWindowSurface(sdl_win);
 			SDL_Surface		*image_surface = SDL_LoadBMP("image.bmp");
 			SDL_BlitSurface(image_surface, NULL, window_surface, NULL);
 			SDL_BlitSurface(image_surface, NULL, window_surface, &((SDL_Rect){0, 400, 10, 10}));
 			SDL_BlitSurface(image_surface, &((SDL_Rect){0, 0, 50, 50}), window_surface, &((SDL_Rect){500, 300, 10, 10}));// seul x et y sont utilise dans le Rect dest
 			SDL_FreeSurface(image_surface);
 			SDL_BlitSurface(image_surface, &((SDL_Rect){0, 0, 10, 10}), window_surface, NULL);
 			SDL_SetWindowFullscreen(sdl_win, SDL_WINDOW_FULLSCREEN);
 			SDL_SetWindowFullscreen(sdl_win, SDL_WINDOW_FULLSCREEN_DESKTOP);
 			while (1)
 				;
 			SDL_UpdateWindowSurface(sdl_win);
 		}
 		SDL_Delay(5000);
 if (1)	{// Print des différents modes d'affichages
 			int	modeNumber = SDL_GetNumDisplayModes(0);
 			if (modeNumber < 0)
 			{
 				fprintf(stdout,"Échec lors de la récupération du nombre de modes (%s)\n",SDL_GetError());
 				return -2;
 			}
 			fprintf(stdout,"Vous avez %d mode(s) d'affichage\n",modeNumber);
 			for (int i = 0 ; i < modeNumber; i++)
 			{
 				SDL_DisplayMode	displayMode;
 				int error = SDL_GetDisplayMode(0,i,&displayMode);
 				if (error < 0)
 				{
 					fprintf(stdout,"Échec lors de la récupération du mode d'affichage (%s)\n",SDL_GetError());
 					return -3;
 				}
 				fprintf(stdout,"Mode %d  \t%dx%d, %d fps\n", i + 1, displayMode.w, displayMode.h, displayMode.refresh_rate);
 			}
 		}// Affichage des différents modes
 if (!i)	{// Renderer
 			SDL_Renderer *pRenderer = SDL_CreateRenderer(sdl_win, -1, SDL_RENDERER_ACCELERATED);//  Création d'un SDL_Renderer utilisant l'accélération matérielle
 			if ( pRenderer )
 			{
 				SDL_Surface* pSprite = SDL_LoadBMP("image.bmp");
 				if ( pSprite )
 				{
 					SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer,pSprite);
 					if ( pTexture )
 					{
 						SDL_RenderClear(pRenderer);
 						SDL_Rect dest = { win_x/2 - pSprite->w/2, win_y/2 - pSprite->h/2, pSprite->w, pSprite->h};
 						SDL_RenderCopy(pRenderer,pTexture,NULL,&dest);//  Copie du sprite grâce au SDL_Renderer
 						SDL_RenderPresent(pRenderer);//  Affichage
 						SDL_Delay(10000);
 						SDL_DestroyTexture(pTexture);
 					}
 					else
 						fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
 					SDL_FreeSurface(pSprite);
 				}
 				else
 				fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
 				SDL_DestroyRenderer(pRenderer);
 			}
 			else
 				fprintf(stdout,"Échec de création du renderer (%s)\n",SDL_GetError());
 		}// Renderer

 		SDL_Event	event;
 		int			escape_pressed = 0;
 		while (escape_pressed == 0) {
 			while (SDL_PollEvent(&event) == 1) {/* Traitement de l'événement */
 				if (event.type == SDL_KEYDOWN) {
 					fprintf(stdout, "Un appuie sur une touche : SDL_KEYDOWN\n");
 					fprintf(stdout, "\trépétition ? : %d\n",event.key.repeat);
 					fprintf(stdout, "\tscancode : %d\n",event.key.keysym.scancode);
 					fprintf(stdout, "\tkey : %d\n",event.key.keysym.sym);
 					if ( event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
 						escape_pressed = 1;
 						break ;
 					}
 				}
 				else if (event.type == SDL_KEYUP) {
 					fprintf(stdout, "Un relachement d'une touche : SDL_KEYUP\n");
 					fprintf(stdout, "\trépétition ? : %d\n",event.key.repeat);
 					fprintf(stdout, "\tscancode : %d\n",event.key.keysym.scancode);
 					fprintf(stdout, "\tkey : %d\n",event.key.keysym.sym);
 				}

 				else if (event.type == SDL_MOUSEMOTION) {
 					fprintf(stdout, "Un déplacement de la souris :\n");
 					fprintf(stdout, "\tfenêtre : %d\n",event.motion.windowID);
 					fprintf(stdout, "\tsouris : %d\n",event.motion.which);
 					fprintf(stdout, "\tposition : %d;%d\n",event.motion.x,event.motion.y);
 					fprintf(stdout, "\tdelta : %d;%d\n",event.motion.xrel,event.motion.yrel);
 					fprintf(stdout, "\tdelta : %d;%d\n",event.motion.xrel,event.motion.yrel);
 				}
 				else if (event.type == SDL_MOUSEBUTTONUP) {
 					fprintf(stdout, "Un relachement d'un bouton de la souris :\n");
 					fprintf(stdout, "\tfenêtre : %d\n",event.button.windowID);
 					fprintf(stdout, "\tsouris : %d\n",event.button.which);
 					fprintf(stdout, "\tbouton : %d\n",event.button.button);
 					#if SDL_VERSION_ATLEAST(2,0,2)
 					fprintf(stdout, "\tclics : %d\n",event.button.clicks);
 					#endif
 					fprintf(stdout, "\tposition : %d;%d\n",event.button.x,event.button.y);
 				}
 				else if (event.type == SDL_MOUSEBUTTONDOWN) {
 					fprintf(stdout, "Un appuie sur un bouton de la souris :\n");
 					fprintf(stdout, "\tfenêtre : %d\n",event.button.windowID);
 					fprintf(stdout, "\tsouris : %d\n",event.button.which);
 					fprintf(stdout, "\tbouton : %d\n",event.button.button);
 					#if SDL_VERSION_ATLEAST(2,0,2)
 					fprintf(stdout, "\tclics : %d\n",event.button.clicks);
 					#endif
 					fprintf(stdout, "\tposition : %d;%d\n",event.button.x,event.button.y);
 				}
 				else if (event.type == SDL_MOUSEWHEEL) {
 					fprintf(stdout, "Roulette de la souris :\n");
 					fprintf(stdout, "\tfenêtre : %d\n",event.wheel.windowID);
 					fprintf(stdout, "\tsouris : %d\n",event.wheel.which);
 					fprintf(stdout, "\tposition : %d;%d\n",event.wheel.x,event.wheel.y);
 				}
 				else if (event.type == SDL_WINDOWEVENT) {
 					fprintf(stdout, "Un événement de fenêtre, sur la fenêtre : %d\n",event.window.windowID);
 				// 	 En théorie, ici, il faudrait faire un autre test ou switch pour chaque type de cet événement
 				}
 				else
 					fprintf(stdout, "Événement non traité : %d\n",event.type);
 			}
 		}
 		 SDL_Delay(5 * 1000);
 	}
 	else
 		fprintf(stderr, "Erreur: création de la fenêtre: %s\n", SDL_GetError());
 	SDL_Quit();
 	return (0);
 }

/*

SDL_CreateWindow()			Crée une fenêtre
SDL_CreateWindowFrom()		Crée une fenêtre SDL à partir d'une fenêtre déjà existante
SDL_DestroyWindow()			Détruit une fenêtre
SDL_GetWindowData()			Récupère les données utilisateur associées à la fenêtre
SDL_GetWindowFlags()		Récupère les options actuelles de la fenêtre
SDL_GetWindowGrab()			Détermine si la fenêtre a le focus clavier
SDL_GetWindowPosition()		Récupère la position actuelle de la fenêtre
SDL_GetWindowSize()			Récupère la taille actuelle de la fenêtre
SDL_GetWindowTitle()		Récupère le titre actuel de la fenêtre
SDL_HideWindow()			Cache la fenêtre
SDL_MaximizeWindow()		Agrandit la fenêtre
SDL_MinimizeWindow()		Réduit la fenêtre dans la barre des tâches
SDL_RaiseWindow()			Place la fenêtre devant les autres
SDL_RestoreWindow()			Restaure la taille et la position d'une fenêtre minimisée ou maximisée
SDL_SetWindowData()			(Re)Définit les données utilisateur de la fenêtre
SDL_SetWindowFullscreen()	Passe la fenêtre en plein écran
SDL_SetWindowGrab()			(Re)Donne le focus clavier à cette fenêtre
SDL_SetWindowIcon()			(Re)Définit l'icône de la fenêtre
SDL_SetWindowPosition()		(Re)Définit la position de la fenêtre
SDL_SetWindowSize()			(Re)Définit la taille de la fenêtre
SDL_SetWindowBordered()		(Re)Définit l'affichage des bordures de la fenêtre
SDL_SetWindowTitle()		(Re)Définit le titre de la fenêtre
SDL_ShowWindow()			Affiche la fenêtre

SDL_Surface* SDL_CreateRGBSurfaceFrom(void*  pixels,
                                      int    width,
                                      int    height,
                                      int    depth,
                                      int    pitch,
                                      Uint32 Rmask,
                                      Uint32 Gmask,
                                      Uint32 Bmask,
                                      Uint32 Amask)

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window,
                                 int         index,  -1 generalement
                                 Uint32      flags)
SDL_RenderClear(pRenderer); ~= win_clear
SDL_DestroyRenderer()
SDL_RENDERER_SOFTWARE			Le SDL_Renderer est purement logiciel (solution de repli).
SDL_RENDERER_ACCELERATED		Le SDL_Renderer utilise l'accélération matérielle.
SDL_RENDERER_PRESENTVSYNC		Le SDL_Renderer est synchronisé au rafraichissement de la fenêtre.
SDL_RENDERER_TARGETTEXTURE		Le SDL_Renderer supporte le rendu vers une texture.

SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer,
                                          SDL_Surface*  surface)
SDL_DestroyTexture()

Uint32 format;
int access = 0;
int largeur = 0;
int hauteur = 0;
SDL_QueryTexture(texture,&format, &access, &largeur, &hauteur);

int SDL_RenderCopy(SDL_Renderer*   renderer,
                   SDL_Texture*    texture,
                   const SDL_Rect* srcrect,
                   const SDL_Rect* dstrect)
SDL_RenderCopy() prend en compte tous les champs du rectangle destination.
En effet, les SDL_Renderer sont capables de faire du redimensionnement de sprite à la volée, ainsi,
les informations de largeur et de hauteur sont utiles pour spécifier un quelconque redimensionnement.

void SDL_RenderPresent(SDL_Renderer* renderer) actualise la window avec le renderer

http:alexandre-laurent.developpez.com/tutoriels/sdl-2/les-evenements/
*/
