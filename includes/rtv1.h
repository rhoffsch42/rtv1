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
# define T_LIST			t_str*

# define RGB(r, g, b)	(65536 * (int)(r) + 256 * (int)(g) + (int)(b))
# define RTOD(x)		(x * (180.0f / M_PI))
# define DTOR(x)		(x * M_PI / 180.0f)
# define ROT_RIGHT		-1
# define ROT_LEFT		1

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
# define FOV			90.0f

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

# define SPHERE			0
# define CYLINDER		1
# define CONE			2
# define PLAN			3

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
	t_str				*(*func)(t_env*, t_str*, int);
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
	int					id;
	t_vector3			pos;
	t_vector3			rot;
	t_vector2			step;
}						t_cam;

typedef struct			s_light
{
	int					id;
	t_vector3			pos;
	t_vector3			rot;
	float				intensity;
	struct s_light		*next;
}						t_light;

typedef struct			s_sdl
{
	t_vector2			size;
	t_vector2			mid;
	char				*title;
	SDL_Window			*win;
	SDL_Surface			*surface;
}						t_sdl;

typedef struct			s_obj
{
	int					id;
	int					type;
	t_vector3			pos;
	t_vector3			rot;
	t_vector3			color;
	float				param;
	struct s_obj		*next;
}						t_obj;

typedef struct			s_env
{
	t_chart				chart[YA_CHART_AMT];
	t_sdl				*sdl;
	t_cam				cam;
	float				amblight;
	t_obj				*objs;
	t_light				*lights;
}						t_env;

////debug, a delete apres
int						sdl_test(void);

t_env					*init_env(void);
void					init_sdl(t_sdl *sdl);
void					get_scene(t_env *e, int ac, char **av);
int						is_empty(T_LIST ptr);
T_LIST					del(T_LIST ptr);
T_LIST					remove_list(T_LIST ptr, int (condition)(T_LIST), T_LIST (del)(T_LIST));
void					error_yaml(char *s1, char *s2);
char					*secure_atof(char *s);

void					build_objects(t_env *e, t_str *p, int id);
t_str					*building_algo(t_env *e, t_str *ptr, char **tok, int (**func)(t_env*, t_str*));
t_str					*check_no_value(t_str *ptr);
t_str					*build_win(t_env *e, t_str *ptr, int id);
t_str					*build_amblight(t_env *e, t_str *ptr, int id);
t_str					*build_cam(t_env *e, t_str *ptr, int id);
t_str					*build_light(t_env *e, t_str *ptr, int id);
t_str					*build_cone(t_env *e, t_str *ptr, int id);
t_str					*build_cylinder(t_env *e, t_str *ptr, int id);
t_str					*build_plan(t_env *e, t_str *ptr, int id);
t_str					*build_sphere(t_env *e, t_str *ptr, int id);
void					adjust_objects(t_env *e);
int						build_pos(t_env *e, t_str *ptr);
int						build_rot(t_env *e, t_str *ptr);
int						build_color(t_env *e, t_str *ptr);
int						build_param(t_env *e, t_str *ptr);



void					sdl_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void					raytracer(t_env *e);
t_vector3				substract_vector3(t_vector3 *v1, t_vector3 *v2);
float					scalar_vector3(t_vector3 *v1, t_vector3 *v2);

char					*ft_strtrim_extended(const char *s);
float					ft_atof(char *s);
void					ft_tabdel(char ***tab);
void					rot_vector2(t_vector2 *src, t_vector2 *dst, float rad, float rot_direction);
void					rot_vector3(t_vector3 *src, t_vector3 *dst, t_vector3 rad, float rot_direction);
float					ft_fmodulo(float n, float mod);
float					ft_degree_scale(float degree);
int						color_coef(int val, float coef);

#endif
