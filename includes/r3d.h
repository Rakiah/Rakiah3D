/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:10:22 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 15:28:05 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_H
# define R3D_H

# include <rmath.h>
# include <libft.h>
# include <rcontainers_lists.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include <pornygonz.h>
# include "r3d_typedefs.h"
# include "r3d_defines.h"
# include "r3d_enums.h"
# include "r3d_structs.h"
# include "r3d_input.h"
# include "r3d_loader.h"

/*
**	TRANSFORM METHODS
*/
t_transform		*trs_new_init();
t_transform		*trs_new(t_vector3f *t, t_vector3f *r, t_vector3f *s);
t_vector3f		trs_transform_direction(t_transform *trs, t_vector3f *v);
t_matrix4f		*trs_get_matrix(t_transform *trs);
t_transform		*trs_get_child(t_transform *parent, int child_index);
void			trs_recalculate_matrix(t_transform *trs);
void			trs_set_dirty(t_transform *trs);
void			trs_set_child(t_transform *parent, t_transform *child);
void			trs_set_pos(t_transform *trs, t_vector3f *new_pos);
void			trs_set_pos_x(t_transform *trs, float x);
void			trs_set_pos_y(t_transform *trs, float y);
void			trs_set_pos_z(t_transform *trs, float z);
void			trs_set_rot(t_transform *trs, t_vector3f *new_rot);
void			trs_set_rot_x(t_transform *trs, float x);
void			trs_set_rot_y(t_transform *trs, float y);
void			trs_set_rot_z(t_transform *trs, float z);
void			trs_set_scale(t_transform *trs, t_vector3f *new_scale);
void			trs_set_scale_x(t_transform *trs, float x);
void			trs_set_scale_y(t_transform *trs, float y);
void			trs_set_scale_z(t_transform *trs, float z);
void			trs_translate(t_transform *trs, t_vector3f *new_pos);
void			trs_rotate(t_transform *trs, t_vector3f *new_rot);
void			trs_scale(t_transform *trs, t_vector3f *new_scale);
/*
**	ENV METHODS
*/

t_core			*get_core(void);
t_window		*core_select_window(int win);
void			core_init(void (*update)(), int width, int height, int fcap);
void			core_add_loader(t_floader loader, char *extension);
void			core_show_cursor(t_bool state);
void			core_lock_cursor(t_bool state);
void			core_start();
void			core_render();
/*
**	RESOURCES METHODS
*/
void			resources_load();
void			resources_add(char *name, void *data);
void			*resources_find(char *name);
/*
**	WINDOW METHODS
*/
t_window		*window_new(int x, int y, char *title);
void			clear_z_buffer();
/*
**	CAMERA METHODS
*/
t_camera		*camera_new_init();
t_camera		*camera_new(t_projection_type type,
							t_transform *transform);
t_matrix4f		*camera_get_matrix(t_camera *camera);
void			camera_set_projection(t_camera *camera,
						t_projection_type project);
void			camera_recalculate_matrix(t_camera *camera);
/*
**	MESH METHODS
*/
t_mesh			*mesh_new_init();
void			mesh_draw(t_mesh *mesh, t_transform *trs);
void			mesh_update_vertices(t_mesh *mesh);
void			mesh_print(t_mesh *mesh);
/*
**	OBJECTS METHODS
*/
t_object		*obj_new_init();
t_object		*obj_new_init_mesh(t_mesh *mesh);
t_object		*obj_new(t_mesh *mesh, t_transform *trs);
void			obj_attach_behaviour(t_object *obj, t_behaviour *behav);
void			obj_draw(t_object *obj);
t_behaviour		*behaviour_new(void (*init)(t_object *, void **),
					void (*start)(t_object *, void *),
					void (*update)(t_object *, void *));
void			behaviour_update(t_list *obj);
/*
**	TEXTURE METHODS
*/
t_texture		*tex_new(int width, int height);
t_texture		*tex_new_surface(int width, int height, SDL_Surface *s);
void			tex_clear(t_texture *tex);
void			tex_draw_pixel(t_texture *tex, int x, int y, int pixel);
void			tex_draw_pixel_index(t_texture *tex, int index, int pixel);
void			tex_to_screen(t_texture *tex, t_core *core);
int				tex_get_pixel(t_texture *tex, int x, int y);
unsigned char	get_pixel_component(int pixel, int index);
int				create_pixel(unsigned char a,
								unsigned char r,
								unsigned char g,
								unsigned char b);
/*
**	MATERIAL METHODS
*/
t_material		*mat_new(t_texture *tex, t_vs_callback vs, t_fs_callback fs);
/*
**	ERROR GESTIONS METHODS
*/
void			error_exit(char *error);
/*
**	INTERNAL METHODS
*/
int				internal_update(t_core *core);
int				internal_key_down_hook(int code);
int				internal_key_up_hook(int code);
int				internal_mouse_down_hook(int code, int x, int y);
int				internal_mouse_up_hook(int code, int x, int y);
int				internal_mouse_pos_hook(int x, int y);
int				internal_mouse_motion_hook(int x, int y);
int				internal_expose_hook();
int				internal_focus_in_hook();
#endif
