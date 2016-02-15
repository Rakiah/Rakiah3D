/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:31:50 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 17:45:07 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

/*void	mesh_draw_wireframe_inner(t_mesh *mesh,*/
				/*t_matrix4f *model_projection,*/
				/*unsigned int *index)*/
/*{*/
	/*int				j;*/
	/*t_vertex		verts[2];*/

	/*j = -1;*/
	/*while (++j < 3)*/
	/*{*/
		/*if (!mesh->draw_hypotenuses && j == 2)*/
			/*continue ;*/
		/*verts[0].pos = trs_transform_point(model_projection,*/
				/*((t_vertex *)mesh->vertices[index[j]])->pos);*/
		/*verts[1].pos = trs_transform_point(model_projection,*/
				/*((t_vertex *)mesh->vertices[index[(j + 1) % 3]])->pos);*/
		/*if (vertex_inside_frustum(&verts[0]) &&*/
			/*vertex_inside_frustum(&verts[1]))*/
		/*{*/
			/*normalise_point(verts[0].pos);*/
			/*normalise_point(verts[1].pos);*/
			/*draw_line(verts[0].pos, verts[1].pos);*/
		/*}*/
		/*free(verts[0].pos);*/
		/*free(verts[1].pos);*/
	/*}*/
/*}*/

void	mesh_draw_filled_inner(t_mesh *mesh,
				t_matrix4f *model_projection,
				unsigned int *index)
{
	t_vertex	v1;
	t_vertex	v2;
	t_vertex	v3;

	(void)model_projection;
	v1 = *(t_vertex *)mesh->vertices[index[0]];
	v2 = *(t_vertex *)mesh->vertices[index[1]];
	v3 = *(t_vertex *)mesh->vertices[index[2]];
	v1.pos = trs_transform_point(model_projection, &v1.pos);
	v2.pos = trs_transform_point(model_projection, &v2.pos);
	v3.pos = trs_transform_point(model_projection, &v3.pos);
	process_polygon(&v1, &v2, &v3, mesh->material);
}

void	mesh_draw(t_mesh *mesh, t_transform *trs)
{
	size_t			i;
	t_matrix4f			model_projection;
	t_core				*core;

	core = get_core();
	m4f_cpy(&model_projection, camera_get_matrix(core->window->camera));
	m4f_mul(&model_projection, trs_get_matrix(trs));
	i = 0;
	while (i < mesh->v_count)
		mesh_draw_filled_inner(mesh, &model_projection,
					(unsigned int *)mesh->indexs[i++]);
}

void	mesh_print(t_mesh *mesh)
{
	size_t	i;

	i = 0;
	while (i < mesh->v_count)
	{
		ft_putstr("TRI NUMBER ");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putstr("END TRI\n");
		i++;
	}
}
