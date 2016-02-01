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
	t_vertex	*pre_next_verts[2];
	float		pre_next_component[2];
	t_bool		pre_next_inside[2];

	pre_next_verts[0] = vertices->end->data;
	pre_next_component[0] = ((float *)pre_next_verts[0]->pos)[index] * side;
	pre_next_inside[0] = pre_next_component[0] <= pre_next_verts[0]->pos->w;
	list_set_start(vertices);
	while ((pre_next_verts[1] = list_next(vertices)) != NULL)
	{
		/*list_next(vertices);*/
		/*pre_next_verts[1] = list_next(vertices);*/
		pre_next_component[1] = ((float *)pre_next_verts[1]->pos)[index] * side;
		pre_next_inside[1] = pre_next_component[1] <= pre_next_verts[1]->pos->w;
		if (pre_next_inside[1] ^ pre_next_inside[0])
		{
			list_push_back(result, vertex_lerp(pre_next_verts[0],
					pre_next_verts[1],
					vertex_new(v4f_new(0, 0, 0, 0),
						v2f_new(0, 0),
						v3f_new(0, 0, 0)),
					(pre_next_verts[0]->pos->w - pre_next_component[0]) /
					((pre_next_verts[0]->pos->w - pre_next_component[0]) -
					(pre_next_verts[1]->pos->w - pre_next_component[1]))));
			/*ft_putstr("correct\n");*/
		}
		if (pre_next_inside[1])
		{
			/*ft_putstr("bite\n");*/
			list_push_back(result, pre_next_verts[1]);
		}
		pre_next_verts[0] = pre_next_verts[1];
		pre_next_component[0] = pre_next_component[1];
		pre_next_inside[0] = pre_next_inside[1];
	}
}

t_bool	clip_axis(t_list *vertices, t_list *tmp, int index)
{
	clip_polygon_index(vertices, tmp, index, 1.0f);
	list_clear(vertices);
	if (tmp->count == 0)
		return (FALSE);
	ft_putnbr(tmp->count);
	ft_putchar('\n');
	clip_polygon_index(tmp, vertices, index, -1.0f);
	list_clear(tmp);
	if (vertices->count == 0)
		return (FALSE);
	/*ft_putstr("vertices count ");*/
	/*ft_putnbr(vertices->count);*/
	/*ft_putchar('\n');*/
	/*ft_putstr("index ");*/
	/*ft_putnbr(index);*/
	/*ft_putchar('\n');*/
	return (TRUE);
}

void	print_list(t_list *list)
{
	ft_putnbr(list->count);
	ft_putchar('\n');
}

void	clip_triangle(t_vertex *verts[3], t_material *mat)
{
	t_list		*remapped;
	t_list		*temporary;
	t_bool		visible[3];
	t_bool		clipped[3];
	int		i;

	visible[0] = vertex_inside_frustum(verts[0]);
	visible[1] = vertex_inside_frustum(verts[1]);
	visible[2] = vertex_inside_frustum(verts[2]);
	clipped[0] = FALSE;
	clipped[1] = FALSE;
	clipped[2] = FALSE;
	if (visible[0] && visible[1] && visible[2])
	{
		draw_triangle(verts, mat);
		return ;
	}
	if (!visible[0] && !visible[1] && !visible[2])
		return ;
	remapped = list_new(sizeof(t_vertex *));
	temporary = list_new(sizeof(t_vertex *));
	list_push_back(remapped, verts[0]);
	list_push_back(remapped, verts[1]);
	list_push_back(remapped, verts[2]);
	/*ft_putstr("have to remap\n");*/
	/*ft_putstr("start clip triangle ");*/
	/*print_list(remapped);*/

	if ((clipped[0] = clip_axis(remapped, temporary, 0)))
	{
		/*ft_putstr("remapped ");*/
		/*print_list(remapped);*/
		/*ft_putstr("temporary ");*/
		/*print_list(temporary);*/
		if ((clipped[1] = clip_axis(remapped, temporary, 1)))
		{
			clipped[2] = clip_axis(remapped, temporary, 2);
		}
	}
	if (clipped[0] && clipped[1] && clipped[2])
	{
		ft_putstr("clipped");
		verts[0] = remapped->start->data;
		i = 1;
		while (i < (int)remapped->count - 1)
		{
			verts[1] = list_get_data_at(remapped, i);
			verts[2] = list_get_data_at(remapped, i + 1);
			draw_triangle(verts, mat);
			i++;
		}
	}
	/*else*/
	/*{*/
		/*ft_putstr("clipped triangles : ");*/
		/*ft_putnbr(clipped[0]);*/
		/*ft_putstr(" ");*/
		/*ft_putnbr(clipped[1]);*/
		/*ft_putstr(" ");*/
		/*ft_putnbr(clipped[2]);*/
		/*ft_putstr("\n");*/
	/*}*/
}

/*void		clip_triangle(t_vertex *verts[3], t_material *mat)*/
/*{*/
	/*if (vertex_inside_frustum(verts[0]) &&*/
		/*vertex_inside_frustum(verts[1]) &&*/
		/*vertex_inside_frustum(verts[2]))*/
		/*draw_triangle(verts, mat);*/
/*}*/

void		draw_triangle(t_vertex *verts[3], t_material *mat)
{
	int				i;
	t_vertex		*swap;

	normalise_point(verts[0]->pos);
	normalise_point(verts[1]->pos);
	normalise_point(verts[2]->pos);
	i = 0;
	while (i < 2)
	{
		if (verts[i]->pos->y > verts[i + 1]->pos->y)
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
	t_interpolant	ipls[INTERPOLANTS_COUNT];

	ipl_set_rendering(ipls, verts);
	side = calculate_triangle_side(verts[0]->pos, verts[2]->pos, verts[1]->pos);
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

void		normalise_point(t_vector4f *vector)
{
	t_vector4f	*tmp;

	tmp = trs_transform_point(&get_core()->window->screen_matrix, vector);
	vector->x = tmp->x / tmp->w;
	vector->y = tmp->y / tmp->w;
	vector->z = tmp->z / tmp->w;
	vector->w = tmp->w;
	free(tmp);
}
