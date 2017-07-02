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
# include <SDL2/SDL.h>
# include <math.h>
# include <stdio.h>

# define ENDL			ft_putchar(10);
# define SPACE			ft_putchar(32);
# define LIST_TYPE		t_str*

# define RGB(r, g, b)(65536 * (int)(r) + 256 * (int)(g) + (int)(b))

# define DEF_WIN_TITLE	"Default title"
# define DEF_WIN_X		800
# define DEF_WIN_Y		600
# define MAX_WIN_X		1920
# define MAX_WIN_Y		1080
# define MIN_WIN_X		800
# define MIN_WIN_Y		600
# define FLOAT_MAX_LEN	7
# define COLOR_MAX		255
# define TITLE_MAX_LEN	50
# define TITLE_TRUNC	"[...]"
# define DRAW_DIST		5.0000f
# define SCREEN_DIST	500.0f

# define YA_SEPARATOR	':'
# define YA_LIST		"- "
# define YA_COMMENT		'#'

# define YA_WIN			"window"
# define YA_AMBLIGHT	"ambiantlight"
# define YA_CAM			"cam"
# define YA_LIGHT		"light"
# define YA_CONE		"cone"
# define YA_PLAN		"plan"
# define YA_SPHERE		"sphere"
# define YA_CYLINDER	"cylinder"

# define YA_TITLE		"title"
# define YA_SIZE		"size"
# define YA_POS			"pos"
# define YA_ROT			"rot"
# define YA_STEP		"step"
# define YA_INTENSITY	"intensity"
# define YA_COLOR		"color"
# define YA_ANGLE		"angle"
# define YA_RAY			"ray"

# define Y_TITLE		1
# define Y_SIZE			2
# define Y_POS			4
# define Y_ROT			8
# define Y_STEP			16
# define Y_INTENSITY	32
# define Y_COLOR		64
# define Y_ANGLE		128
# define Y_RAY			256

# define YA_CHART_AMT	17
# define YA_CHART_OBJ	8
# define YA_CHAR		0
# define YA_FLOAT		1

# define YA_ERROR		"Error : bad yaml format"
# define YA_BAD_TOKEN	"Error : unknow token"
# define YA_BAD_FLOAT	"Error : invalid float value"
# define OK				0
# define BAD_ARGS		0
# define OPEN_FAIL		0
# define MALLOC_FAIL	0
# define YA_BAD_FORMAT	0
# define SDL_FAIL		0
# define SDL_BAD_BPP	0

typedef struct s_env t_env;

typedef struct			s_str
{
	char				*str;
	struct s_str		*next;
}						t_str;

typedef struct			s_chart
{
	char				*key_name;
	char				val_amount;
	char				val_type;
	int					values;
	t_str				*(*func)(t_env*, t_str*);
}						t_chart;

typedef struct			s_vector2
{
	float				x;
	float				y;
}						t_vector2;

typedef struct			s_vector3
{
	float				x;
	float				y;
	float				z;
}						t_vector3;

typedef struct			s_cam
{
	t_vector3			pos;
	t_vector3			rot;
	t_vector2			step;
}						t_cam;

typedef struct			s_light
{
	t_vector3			pos;
	t_vector3			rot;
	float				intensity;
	struct s_light		*next;
}						t_light;

typedef struct			s_cone
{
	t_vector3			pos;
	t_vector3			rot;
	t_vector3			color;
	float				angle;
	struct s_cone		*next;
}						t_cone;

typedef struct			s_cylinder
{
	t_vector3			pos;
	t_vector3			rot;
	t_vector3			color;
	float				r;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct			s_plan
{
	t_vector3			pos;
	t_vector3			rot;
	t_vector3			color;
	struct s_plan		*next;
}						t_plan;

typedef struct			s_sphere
{
	t_vector3			pos;
	t_vector3			rot;
	t_vector3			color;
	float				r;
	struct s_sphere		*next;
}						t_sphere;

typedef struct			s_sdl
{
	t_vector2			size;
	t_vector2			mid;
	char				*title;
	SDL_Window			*win;
	SDL_Surface			*surface;
}						t_sdl;

typedef struct			s_env
{
	t_chart				chart[YA_CHART_AMT];
	t_sdl				*sdl;
	t_cam				cam;
	float				amblight;
	t_light				*lights;
	t_sphere			*spheres;
	t_cone				*cones;
	t_plan				*plans;
	t_cylinder			*cylinders;
}						t_env;

////debug, a delete apres
int						sdl_test(void);
int						build_pos1(t_env *e, t_str *ptr, t_vector3 *obj);
int						build_rot1(t_env *e, t_str *ptr, t_vector3 *obj);
int						build_color1(t_env *e, t_str *ptr, t_vector3 *obj);
int						build_ray1(t_env *e, t_str *ptr, float *ray);
int						fill_vector(char *src, void *ptr, int size);
t_str					*building_algo1(t_env *e, t_str *ptr, char **tok, int (**func)(char*, void*, int));

t_env					*init_env(void);
void					init_sdl(t_sdl *sdl);
void					get_scene(t_env *e, int ac, char **av);
int						is_empty(LIST_TYPE ptr);
LIST_TYPE				remove_list(LIST_TYPE ptr, int (f)(LIST_TYPE));
void					error_yaml(char *s1, char *s2);
char					*secure_atof(char *s);

void					build_objects(t_env *e, t_str *ptr);
t_str					*building_algo(t_env *e, t_str *ptr, char **tok, int (**func)(t_env*, t_str*));
t_str					*check_no_value(t_str *ptr);
t_str					*build_win(t_env *e, t_str *ptr);
t_str					*build_amblight(t_env *e, t_str *ptr);
t_str					*build_cam(t_env *e, t_str *ptr);
t_str					*build_light(t_env *e, t_str *ptr);
t_str					*build_cone(t_env *e, t_str *ptr);
t_str					*build_cylinder(t_env *e, t_str *ptr);
t_str					*build_plan(t_env *e, t_str *ptr);
t_str					*build_sphere(t_env *e, t_str *ptr);
void					adjust_objects(t_env *e);

void					sdl_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void					raytracer(t_env *e);
t_vector3				substract_vector3(t_vector3 *v1, t_vector3 *v2);
float					scalar_vector3(t_vector3 *v1, t_vector3 *v2);

char					*ft_strtrim_extended(const char *s);
float					ft_atof(char *s);
void					ft_tabdel(char ***tab);

#endif
