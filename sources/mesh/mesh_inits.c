/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:33:01 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/09 19:14:57 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_mesh		*mesh_new_init(void)
{
	t_mesh	*ret;

	ret = (t_mesh *)malloc(sizeof(t_mesh));
	ret->vertices = NULL;
	ret->indices = NULL;
	ret->v_count = 0;
	ret->i_count = 0;
	ret->vbo = pornygonz_create_vertex_array();
	ret->ibo = pornygonz_create_index_array();
	ret->wireframe = FALSE;
	ret->material = mat_new_init();
	return (ret);
}

static void	create_vertex_buffer(t_vertex **verts, void *buffer, int v_count)
{
	int i;

	i = -1;
	while (++i < v_count)
		rstd_memcpy(buffer + i * sizeof(t_vertex), verts[i], sizeof(t_vertex));
}

static void	create_index_buffer(unsigned int **ids, unsigned int *b, int count)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while (++i < count)
	{
		b[j++] = ids[i][0];
		b[j++] = ids[i][1];
		b[j++] = ids[i][2];
	}
}

void		mesh_update_vertices(t_mesh *mesh)
{
	float			*vertex_buffer;
	unsigned int	*index_buffer;

	vertex_buffer = (float *)malloc(mesh->v_count * sizeof(t_vertex));
	index_buffer = malloc(mesh->i_count * 3 * sizeof(int));
	create_vertex_buffer(mesh->vertices, vertex_buffer, mesh->v_count);
	create_index_buffer(mesh->indices, index_buffer, mesh->i_count);
	pornygonz_bind_vertex_array(mesh->vbo);
	pornygonz_bind_index_array(mesh->ibo);
	pornygonz_add_vertex_data(vertex_buffer, mesh->v_count * sizeof(t_vertex));
	pornygonz_add_index_data(index_buffer, mesh->i_count * 3 * sizeof(int));
	free(vertex_buffer);
	free(index_buffer);
}
