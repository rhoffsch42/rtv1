/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoffsch <rhoffsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:02 by rhoffsch          #+#    #+#             */
/*   Updated: 2017/05/24 14:02:47 by rhoffsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <libft.h>
//# include <SDL2/SDL.h>
# include <math.h>

# define DEF_WIN_TITLE	"Default title"
# define DEF_WIN_X		800
# define DEF_WIN_Y		600
# define MAX_WIN_X		800
# define MAX_WIN_Y		600

# define YA_SEPARATOR	':'
# define YA_LIST		"- "
# define YA_COMMENT		'#'
# define YA_WIN			"window"
# define YA_TITLE		"title"
# define YA_SIZE		"size"
# define YA_AMBLIGHT	"ambiantlight"
# define YA_CAM			"cam"
# define YA_LIGHT		"light"
# define YA_CONE		"cone"
# define YA_PLAN		"plan"
# define YA_SPHERE		"sphere"
# define YA_CYLINDER	"cylinder"
# define YA_POS			"pos"
# define YA_ROT			"rot"
# define YA_STEP		"step"
# define YA_INTENSITY	"intensity"
# define YA_COLOR		"color"
# define YA_ANGLE		"angle"
# define YA_RAY			"ray"

# define OK				0
# define BAD_ARGS		0
# define SDL_FAIL		0
# define OPEN_FAIL		0
# define MALLOC_FAIL	0

typedef struct		s_str
{
	char			*str;
	struct s_str	*next;
}					t_str;

typedef struct		s_vector2
{
	float			x;
	float			y;
}					t_vector2;

typedef struct		s_vector3
{
	float			x;
	float			y;
	float			z;
}					t_vector3;

typedef struct		s_cam
{
	t_vector3		pos;
	t_vector3		rot;
	t_vector2		step;
}					t_cam;

typedef struct		s_light
{
	t_vector3		pos;
	t_vector3		rot;
	float			intensity;
}					t_light;

typedef struct		s_cone
{
	t_vector3		pos;
	t_vector3		rot;
	t_vector3		color;
	float			angle;
}					t_cone;

typedef struct		s_cylinder
{
	t_vector3		pos;
	t_vector3		rot;
	t_vector3		color;
	float			r;
}					t_cylinder;

typedef struct		s_plan
{
	t_vector3		pos;
	t_vector3		rot;
	t_vector3		color;
}					t_plan;

typedef struct		s_sphere
{
	t_vector3		pos;
	t_vector3		rot;
	t_vector3		color;
	float			r;
}					t_sphere;

typedef struct		s_sdl
{
	int				win_x;
	int				win_y;
	char			*title;
	// SDL_Window		*win;
	// SDL_Surface		*surface;
}					t_sdl;

typedef struct		s_env
{
	t_sdl			*sdl;
	t_light			*lights;
	t_sphere		*spheres;
	t_cone			*cones;
	t_plan			*plans;
	t_cylinder		*cylinders;
}					t_env;

////debug, a delete apres
int					sdl_test(void);

t_env				*init_env(void);
void				init_sdl(t_sdl *sdl);
void				get_scene(t_env *e, int ac, char **av);
t_str				*get_file(char *filename);

#endif
