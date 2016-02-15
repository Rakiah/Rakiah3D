/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 21:22:20 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void	clip_polygon_index(t_list *vertices, t_list *result, int index, float side)
{
	t_vertex	*verts[2];
	float		component[2];
	t_bool		inside[2];

	verts[0] = vertices->end->data;
	component[0] = ((float *)(&verts[0]->pos))[index] * side;
	inside[0] = component[0] <= verts[0]->pos.w;
	while ((verts[1] = list_next(vertices)) != NULL)
	{
		component[1] = ((float *)(&verts[1]->pos))[index] * side;
		inside[1] = component[1] <= verts[1]->pos.w;
		if (inside[1] ^ inside[0])
			list_push_back(result, vertex_lerp(verts[0],
					verts[1], vertex_new_init(),
					(verts[0]->pos.w - component[0]) /
					((verts[0]->pos.w - component[0]) -
					(verts[1]->pos.w - component[1]))));
		if (inside[1])
			list_push_back(result, vertex_new_cpy(verts[1]));
		verts[0] = verts[1];
		component[0] = component[1];
		inside[0] = inside[1];
	}
}

t_bool	clip_axis(t_list *vertices, t_list *tmp, int index)
{
	clip_polygon_index(vertices, tmp, index, 1.0f);
	list_clear_inner(vertices, list_default_remove_functor);
	if (tmp->count == 0)
		return (FALSE);
	clip_polygon_index(tmp, vertices, index, -1.0f);
	list_clear_inner(tmp, list_default_remove_functor);
	if (vertices->count == 0)
		return (FALSE);
	return (TRUE);
}

void	process_polygon(t_vertex *v1, t_vertex *v2, t_vertex *v3, t_material *mat)
{
	t_bool		visible[3];
	t_list		*clipped_triangle;
	int		i;

	visible[0] = vertex_inside_frustum(v1);
	visible[1] = vertex_inside_frustum(v2);
	visible[2] = vertex_inside_frustum(v3);
	
	if (visible[0] && visible[1] && visible[2])
	{
		process_triangle(*v1, *v2, *v3, mat);
		return ;
	}
	clipped_triangle = clip_triangle(v1, v2, v3);
	if (clipped_triangle == NULL || clipped_triangle->count == 0)
		return ;
	v1 = clipped_triangle->start->data;
	i = 1;
	while (i < (int)clipped_triangle->count - 1)
	{
		v2 = list_get_data_at(clipped_triangle, i);
		v3 = list_get_data_at(clipped_triangle, i + 1);
		process_triangle(*v1, *v2, *v3, mat);
		i++;
	}
	list_clear_inner(clipped_triangle, list_default_remove_functor);
	free(clipped_triangle);
}

void	process_triangle(t_vertex v1, t_vertex v2, t_vertex v3, t_material *mat)
{
	t_vertex *verts[3];

	v1.pos = normalise_point(&v1.pos);
	v2.pos = normalise_point(&v2.pos);
	v3.pos = normalise_point(&v3.pos);
	verts[0] = &v1;
	verts[1] = &v2;
	verts[2] = &v3;
	draw_triangle(verts, mat);
}

t_list	*clip_triangle(t_vertex *v1, t_vertex *v2, t_vertex *v3)
{
	t_list		*remapped;
	t_list		*temporary;

	remapped = list_new(sizeof(t_vertex *));
	temporary = list_new(sizeof(t_vertex *));
	list_push_back(remapped, vertex_new_cpy(v1));
	list_push_back(remapped, vertex_new_cpy(v2));
	list_push_back(remapped, vertex_new_cpy(v3));
	if (!clip_axis(remapped, temporary, 0) ||
		!clip_axis(remapped, temporary, 1) ||
		!clip_axis(remapped, temporary, 2))
	{
		free(temporary);
		free(remapped);
		return (NULL);
	}
	free(temporary);
	return (remapped);
}

t_vector4f	normalise_point(t_vector4f *vector)
{
	t_vector4f	tmp;

	tmp = trs_transform_point(&get_core()->window->screen_matrix, vector);
	tmp.x /= tmp.w;
	tmp.y /= tmp.w;
	tmp.z /= tmp.w;
	return (tmp);
}

void		draw_triangle(t_vertex *verts[3], t_material *mat)
{
	int				i;
	t_vertex			*swap;


	if (calculate_triangle_side(&verts[0]->pos, &verts[2]->pos, &verts[1]->pos))
		return ;
	i = 0;
	while (i < 2)
	{
		if (verts[i]->pos.y > verts[i + 1]->pos.y)
		{
			swap = verts[i];
			verts[i] = verts[i + 1];
			verts[i + 1] = swap;
			i = -1;
		}
		i++;
	}
	triangle_to_lines(verts, mat);
}

void		triangle_to_lines(t_vertex *verts[3], t_material *mat)
{
	t_bool			side;
	t_line			lines[3];
	t_line			*send_lines[2];
	t_vertex		*send_verts[2];
	t_interpolant		ipls[INTERPOLANTS_COUNT];

	ipl_set_rendering(ipls, verts);
	side = calculate_triangle_side(&verts[0]->pos, &verts[2]->pos, &verts[1]->pos);
	send_verts[0] = verts[0];
	send_verts[1] = verts[2];
	line_setup(&lines[0], send_verts, ipls, 0);
	send_verts[0] = verts[0];
	send_verts[1] = verts[1];
	line_setup(&lines[1], send_verts, ipls, 0);
	send_verts[0] = verts[1];
	send_verts[1] = verts[2];
	line_setup(&lines[2], send_verts, ipls, 1);
	send_lines[0] = &lines[0];
	send_lines[1] = &lines[1];
	draw_between_line(send_lines, side, mat);
	send_lines[0] = &lines[0];
	send_lines[1] = &lines[2];
	draw_between_line(send_lines, side, mat);
}

t_bool		calculate_triangle_side(t_vector4f *a, t_vector4f *b, t_vector4f *c)
{
	return (((b->x - a->x) * (c->y - a->y) -
		(c->x - a->x) * (b->y - a->y)) >= 0 ? 1 : 0);
}
