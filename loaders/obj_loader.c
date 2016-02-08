/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 07:04:05 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 18:27:30 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <fcntl.h>

void	create_vertex(t_obj_index *index, t_list *vertices, t_obj_model *model)
{
	t_vertex	*v_tmp;

	v_tmp = vertex_new_init();
	v_tmp->pos = *(t_vector4f *)list_get_data_at(model->pos,
					index->i[0]);
	if (index->i[1] >= 0)
		v_tmp->tex_coords =
			*(t_vector2f *)list_get_data_at(model->tex_coords,
							index->i[1]);
	else
		v2f_set(&v_tmp->tex_coords, 0, 0);
	if (index->i[2] >= 0)
		v_tmp->normals =
			*(t_vector3f *)list_get_data_at(model->normals,
						index->i[2]);
	else
		v3f_set(&v_tmp->normals, 0, 0, 0);
	list_push_back(vertices, v_tmp);
}

void		arrange_vertices_obj(t_obj_model *model,
					t_list *vertices,
					t_list *index_m)
{
	int				i;
	int				index;
	unsigned int			*tri;
	t_obj_index			*indexes;

	indexes = list_next(model->index);
	index = 0;
	while (indexes != NULL)
	{
		if ((tri = malloc(sizeof(int) * 3)) == NULL)
			error_exit("MEMORY ALLOCTION FAILED");
		i = -1;
		while (++i < 3)
		{
			create_vertex(indexes, vertices, model);
			indexes = list_next(model->index);
			tri[i] = index++;
		}
		list_push_back(index_m, tri);
	}
}

void	*load_obj(char *path)
{
	int		fd;
	t_obj_model	*model;
	t_list		*lists[2];
	t_mesh		*mesh;

	mesh = mesh_new_init();
	lists[0] = list_new(sizeof(t_vertex *));
	lists[1] = list_new(sizeof(t_vertex *));
	if ((fd = open(path, O_RDONLY)) < 0)
		error_exit(ft_strjoin("COULDN'T FIND FILE AT : ", path));
	model = obj_model_new(fd);
	arrange_vertices_obj(model, lists[0], lists[1]);
	mesh->v_count = lists[1]->count;
	mesh->vertices = (t_vertex **)list_to_array(lists[0]);
	mesh->indexs = (unsigned int **)list_to_array(lists[1]);
	close(fd);
	return (mesh);
}
