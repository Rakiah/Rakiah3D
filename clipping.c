#include "r3d.h"

void	clip_polygon_index(t_list *vertices, t_list *result, int index, float side)
{
	t_vertex	*pre_next_verts[2];
	t_vertex	*tmp;
	float		pre_next_component[2];
	t_bool		pre_next_inside[2];
	t_list		*it;

	pre_next_verts[0] = *(t_vertex **)ft_lst_get_end(vertices)->content;
	pre_next_component[0] = ((float *)pre_next_verts[0]->pos)[index] * side;
	pre_next_inside[0] = pre_next_component[0] <= pre_next_verts[0]->pos->w;
	it = vertices;
	while (it->next != NULL)
	{
		pre_next_verts[1] = *(t_vertex **)it->next->content;
		pre_next_component[1] = ((float *)pre_next_verts[1]->pos)[index] * side;
		pre_next_inside[1] = pre_next_component[1] <= pre_next_verts[1]->pos->w;

		if (pre_next_inside[1] ^ pre_next_inside[0])
		{
			tmp = vertex_lerp(pre_next_verts[0], pre_next_verts[1], vertex_new(v4f_new(0, 0, 0, 0),
												v2f_new(0, 0, 0),
												v3f_new(0, 0, 0)),
					(pre_next_verts[0]->pos->w - pre_next_component[0]) /
					((pre_next_verts[0]->pos->w - pre_next_component[0]) -
					 (pre_next_verts[1]->pos->w - pre_next_component[1])));
			result->next = ft_lstnew(&tmp, sizeof(t_vertex *));
		}
		if (pre_next_inside[1])
		{
			result->next = ft_lstnew(&pre_next_verts[1], sizeof(t_vertex *));
			result = result->next;
		}
		pre_next_verts[0] = pre_next_verts[1];
		pre_next_component[0] = pre_next_component[1];
		pre_next_inside[0] = pre_next_inside[1];
	}
}

t_bool	clip_axis(t_list *vertices, int index)
{
	t_list	*tmp;

	tmp = ft_lstnew(NULL, 0);
	clip_polygon_index(vertices, tmp, index, 1.0f);
	ft_lstdel(vertices, &del_content);
	if (tmp->next == NULL)
		return (FALSE);
	vertices = ft_lstnew(NULL, 0);
	clip_polygon_index(tmp, vertices, index, -1.0f);
	ft_lstdel(tmp, &del_content);
	return (vertices->next);
}

void	clip_triangle(t_vertex *verts[3], t_material *mat)
{
	t_list	*remapped;
	t_list	*start;
	size_t	i;

	if (vertex_inside_frustum(verts[0]) &&
		vertex_inside_frustum(verts[1]) &&
		vertex_inside_frustum(verts[2]))
	{
		draw_triangle(verts, mat);
		return ;
	}
	remapped = ft_lstnew(&verts[0], sizeof(t_vertex *));
	remapped->next = ft_lstnew(&verts[1], sizeof(t_vertex *));
	remapped->next->next = ft_lstnew(&verts[2], sizeof(t_vertex *));
	if (clip_axis(remapped, 0) && clip_axis(remapped, 1) && clip_axis(remapped, 2))
	{
		start = remapped;
		remapped = remapped->next;
		verts[0] = *(t_vertex **)remapped->content;
		remapped = remapped->next;
		while (remapped->next != NULL)
		{
			verts[1] = *(t_vertex **)remapped->content;
			verts[2] = *(t_vertex **)remapped->next->content;
			draw_triangle(verts, mat);
			remapped = remapped->next;
		}
	}
}
