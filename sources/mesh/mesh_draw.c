/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:31:50 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/06 22:55:28 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void	mesh_draw(t_mesh *mesh, t_transform *trs)
{
	t_matrix4f			model_projection;
	t_core				*core;

	core = get_core();
	model_projection = *(camera_get_matrix(core->camera));
	/*m4f_cpy(&model_projection, camera_get_matrix(core->camera));*/
	m4f_mul(&model_projection, trs_get_matrix(trs));
	pornygonz_add_uniform("MVP", &model_projection, sizeof(t_matrix4f));
	pornygonz_enable_vertex_attribute(PORNYGONZ_TEXTURE_COORDS | PORNYGONZ_NORMALS);
	pornygonz_bind_vertex_shader(mesh->material->vs);
	pornygonz_bind_fragment_shader(mesh->material->fs);
	if (mesh->material->texture != NULL)
		pornygonz_bind_texture(mesh->material->texture->tbo);
	else
		pornygonz_bind_texture(0);
	pornygonz_bind_vertex_array(mesh->vbo);
	pornygonz_bind_index_array(mesh->ibo);
	pornygonz_draw_elements(PORNYGONZ_TRIANGLES, PORNYGONZ_UNSIGNED_INT, 0, mesh->i_count * 3);
	pornygonz_disable_vertex_attribute(PORNYGONZ_TEXTURE_COORDS | PORNYGONZ_NORMALS);
}
