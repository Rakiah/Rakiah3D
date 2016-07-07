/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_loader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:30:11 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 01:23:35 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_LOADER_H
# define R3D_LOADER_H

typedef	struct s_obj_model	t_obj_model;
typedef struct s_obj_index	t_obj_index;

struct			s_obj_model
{
	int			count;
	int			component_count;
	t_list		*pos;
	t_list		*tex_coords;
	t_list		*normals;
	t_list		*indices;
};
struct			s_obj_index
{
	int i[3];
};
void			obj_model_delete(t_obj_model *m);
t_obj_model		*obj_model_new(char *path);
t_loader		*find_loader(char *ext);
void			*load_obj(char *path);
void			*load_ro(char *path);
void			*load_image(char *path);
void			*load_rs(char *path);
void			*load(char *path);

#endif
