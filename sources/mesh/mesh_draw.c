/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:31:50 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/09 23:07:28 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void	mesh_draw(t_mesh *mesh, t_transform *trs)
{
	t_matrix4f			model_projection;
	t_material			*material;
	t_core				*core;

	material = mesh->material;
	core = get_core();
	model_projection = *(camera_get_matrix(core->camera));
	m4f_mul(&model_projection, trs_get_matrix(trs));
	pornygonz_add_uniform("MVP", &model_projection, sizeof(t_matrix4f));
	pornygonz_enable_vertex_attribute(PORNYGONZ_TEXTURE_COORDS);
	pornygonz_bind_vertex_shader(material->vs);
	pornygonz_bind_fragment_shader(material->fs);
	pornygonz_bind_texture(material->texture ? material->texture->tbo : 0);
	pornygonz_bind_vertex_array(mesh->vbo);
	pornygonz_bind_index_array(mesh->ibo);
	pornygonz_draw_elements(PORNYGONZ_TRIANGLES, PORNYGONZ_UNSIGNED_INT,
							0, mesh->i_count * 3);
	pornygonz_disable_vertex_attribute(PORNYGONZ_TEXTURE_COORDS);
}
