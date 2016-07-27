/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:30:57 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/27 16:02:47 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_STRUCTS_H
# define R3D_STRUCTS_H

struct						s_vertex
{
	t_vector3f				p;
	t_vector2f				t;
};

struct						s_transform
{
	t_transform				*parent;
	t_list					*childs;
	t_vector3f				position;
	t_vector3f				rotation;
	t_vector3f				scale;
	t_matrix4f				model_world_matrix;
	t_bool					is_dirty;
};

struct						s_texture
{
	unsigned int			tbo;
	void					*pixels;
	int						width;
	int						height;
	int						size;
	int						bytes_per_pixel;
	int						l_size;
};

struct						s_camera
{
	float					fov;
	t_bool					is_dirty;
	t_vector2f				size;
	t_vector2f				z_bounds;
	t_matrix4f				projection;
	t_matrix4f				projected_view;
	t_projection_type		project_type;
	t_transform				*transform;
};

struct						s_material
{
	t_texture				*texture;
	t_vs_callback			vs;
	t_fs_callback			fs;
};

struct						s_resource
{
	char					*name;
	char					*path;
	void					*data;
};

struct						s_core
{
	t_list					*loaders;
	t_list					*objects;
	t_list					*cams;
	t_list					*resources;
	t_camera				*camera;
	void					(*update)();
	void					(*postrender)();
	int						target_framerate;
	double					delta_time;
	void					*data;
	int						width;
	int						height;
	t_bool					shown_cursor;
	t_bool					locked_cursor;
};

struct						s_mesh
{
	unsigned int		vbo;
	unsigned int		ibo;
	t_vertex			**vertices;
	unsigned int		**indices;
	size_t				v_count;
	size_t				i_count;
	t_material			*material;
	t_bool				wireframe;
};

struct						s_object
{
	t_bool				active;
	t_mesh				*mesh;
	t_list				*behaviours;
	t_transform			*transform;
};

struct						s_behaviour
{
	t_bool				active;
	void				*data;
	void				(*init)(t_object *, void **);
	void				(*start)(t_object *, void *);
	void				(*update)(t_object *, void *);
};

struct						s_loader
{
	char				*extension;
	t_floader			method;
};

#endif
