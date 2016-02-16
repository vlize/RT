/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/02/16 09:55:12 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <float.h>
# include <X11/X.h>
# include <math.h>

# define FOV_2 35
# define WIDTH 1280
# define HEIGHT 720
# define RED_0 0
# define BLUE_0 0
# define GREEN_0 0
# define AMBIANT 0.33
# define LIGHT_INT 0xFF
# define SPECULAR_POW 16
# define SPOT_LIGHT_INT 0x155
# define SPOT_LIGHT_POW 4096
# define EPSILON 0.001
# define PI2 6.283185307179587
# define RADIAN 0.01745329251994329
# define INVALID "Invalid file"
# define GNL "get_next_line()"
# define MALLOC "malloc()"
# define CLOSE "close()"
# define PROG "rtv1"
# define COLON ": "
# define CAM "cam"
# define SPOT "spot"
# define CONE "cone"
# define TORE "tore"
# define PLANE "plane"
# define SPHERE "sphere"
# define CYLINDER "cylinder"
# define ELLIPSOID "ellipsoid"
# define PARABOLOID "paraboloid"
# define HYPERBOLOID "hyperboloid"
# define MOBIUS_STRIP "Möbius strip"
# define HYPERBOLIC "hyperbolic"
# define ELLIPTIC "elliptic"
# define SHEET2 "two sheets"
# define SHEET1 "one sheet"
# define PX "px = "
# define PY "py = "
# define PZ "pz = "
# define RX "rx = "
# define RY "ry = "
# define RZ "rz = "
# define RT "R = "
# define R "r = "
# define A "a = "
# define B "b = "
# define C "c = "
# define HEX "0x"

typedef struct		s_vec
{
	float			px;
	float			py;
	float			pz;
	float			vx;
	float			vy;
	float			vz;
	float			pow2_px;
	float			pow2_py;
	float			pow2_pz;
	float			pow2_vx;
	float			pow2_vy;
	float			pow2_vz;
}					t_vec;

typedef struct		s_spot
{
	float			px;
	float			py;
	float			pz;
	struct s_spot	*next;
}					t_spot;

typedef struct		s_obj
{
	char			*type;
	int				nbr;
	int				red;
	int				green;
	int				blue;
	int				sign;
	float			px;
	float			py;
	float			pz;
	float			rx[3];
	float			ry[3];
	float			rz[3];
	float			r;
	float			tan_r;
	float			tan2_r;
	float			pow2_r;
	float			a;
	float			b;
	float			c;
	float			pow2_a;
	float			pow2_b;
	float			pow2_c;
	float			rt;
	float			pow2_rt;
	float			d;
	float			e;
	float			f;
	float			pow2_d;
	float			pow2_e;
	float			pow2_f;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_cam
{
	float			px;
	float			py;
	float			pz;
	float			rx[3];
	float			ry[3];
	float			rz[3];
	float			pow2_px;
	float			pow2_py;
	float			pow2_pz;
	float			pow2_vx[WIDTH][HEIGHT];
	float			pow2_vy[WIDTH][HEIGHT];
	float			pow2_vz[WIDTH][HEIGHT];
	float			vx[WIDTH][HEIGHT];
	float			vy[WIDTH][HEIGHT];
	float			vz[WIDTH][HEIGHT];
}					t_cam;

typedef struct		s_env
{
	float			specular_coef;
	float			depth;
	int				width_2;
	int				height_2;
	int				endian;
	int				size_l;
	int				bpp;
	int				fd;
	int				gnl;
	int				line_nbr;
	int				spot_nbr;
	int				obj_nbr;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	char			*name;
	char			*line;
	t_vec			*vec;
	t_vec			*vec0;
	t_cam			*cam;
	t_obj			*obj;
	t_obj			*obj0;
	t_spot			*spot;
	t_spot			*spot0;
}					t_env;

int					ft_inc_gnl(t_env *env);
int					ft_perror(char *msg, t_env *env);
int					ft_put_error(char *name, char *msg, t_env *env);
int					ft_free_env(t_env *env);
void				ft_init_env(t_env *env);
void				ft_make_obj(t_env *env);
void				ft_read_file(t_env *env);
void				ft_init_vector(t_cam *cam, t_env *env);
void				ft_set_nbr(int i, char *str, float *nbr, t_env *env);
void				ft_set_hex(t_obj *obj, t_env *env);
void				ft_draw(t_env *env);
void				ft_angle_cos_sin(float angle, float angle_cos_sin[3]);
void				ft_rotation_matrix(float *a, float *o, float an[3], int n);
void				ft_vector_rotation(float v[3], t_vec *ve, t_obj *ob, int n);
void				ft_vector_equation(t_obj *obj);
void				ft_set_v0(float *v0, t_vec *vec);
void				ft_set_pt0(float *pt0, t_obj *obj, t_vec *vec);
void				ft_rot_v0_pt0(float *v, float *p, t_obj *obj, t_vec *vec);
float				*ft_rot_pt1(float *pt1, t_obj *obj);
float				*ft_quadratic_equation(float a, float b, float c);
float				*ft_plane(t_obj *obj, t_vec *vec);
float				*ft_sphere(t_obj *obj, t_vec *vec);
float				*ft_cylinder(t_obj *obj, t_vec *vec);
float				*ft_cone(t_obj *obj, t_vec *vec);
float				*ft_tore(t_obj *obj, t_vec *vec);
float				*ft_paraboloid(t_obj *obj, t_vec *vec);
float				*ft_hyperboloid(t_obj *obj, t_vec *vec);
float				*ft_ellipsoid(t_obj *obj, t_vec *vec);
float				*ft_mobius_strip(t_obj *obj, t_vec *vec);
float				*ft_ray_collision(t_obj *obj, t_vec *vec);
int					ft_nearest_point(float pt[4], float *pt1, t_vec *vec);
void				ft_lux_tracing(int *color, float *pt, t_env *env);
void				ft_normal_direction(float *n, t_vec *vec);
void				ft_normal2(float *n, t_env *env);
void				ft_normal(float *v, t_env *env);
void				ft_check_color(int	*color);
void				ft_spot_tracing(int *color, t_env *env);

#endif
