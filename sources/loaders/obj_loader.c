/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 07:04:05 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/09 19:11:43 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <fcntl.h>

void	obj_model_delete(t_obj_model *m)
{
	list_delete_inner(m->pos, list_default_remove_functor);
	list_delete_inner(m->tex_coords, list_default_remove_functor);
	list_delete_inner(m->normals, list_default_remove_functor);
	list_delete_inner(m->indices, list_default_remove_functor);
	free(m);
}

void	create_vertex(t_list *vertices, t_obj_model *m, t_obj_index *i)
{
	t_vertex	*v;

	v = malloc(sizeof(t_vertex));
	v->p = *(t_vector3f *)list_get_data_at(m->pos, i->i[0]);
	if (i->i[1] >= 0)
		v->t = *(t_vector2f *)list_get_data_at(m->tex_coords, i->i[1]);
	else
		v->t = V2F_ZERO;
	list_push_back(vertices, v);
}

void	arrange_vertices_obj(t_obj_model *m, t_list *v, t_list *i)
{
	int				x;
	int				index;
	t_obj_index		*iterator;
	unsigned int	*triangle;

	index = 0;
	iterator = list_next(m->indices);
	while (iterator != NULL)
	{
		triangle = malloc(sizeof(unsigned int) * 3);
		x = -1;
		while (++x < 3)
		{
			create_vertex(v, m, iterator);
			iterator = list_next(m->indices);
			triangle[x] = index++;
		}
		list_push_back(i, triangle);
	}
}

void	*load_obj(char *path)
{
	t_list		*lists[2];
	t_mesh		*mesh;
	t_obj_model	*model;

	mesh = mesh_new_init();
	lists[0] = list_new();
	lists[1] = list_new();
	model = obj_model_new(path);
	arrange_vertices_obj(model, lists[0], lists[1]);
	mesh->v_count = lists[0]->count;
	mesh->i_count = lists[1]->count;
	mesh->vertices = (t_vertex **)list_to_array(lists[0]);
	mesh->indices = (unsigned int **)list_to_array(lists[1]);
	obj_model_delete(model);
	list_delete(lists[0]);
	list_delete(lists[1]);
	mesh_update_vertices(mesh);
	return (mesh);
}
