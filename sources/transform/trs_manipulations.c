/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trs_manipulations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 05:27:20 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 21:18:30 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_transform	*trs_new_init(void)
{
	t_transform *ret;

	ret = (t_transform *)malloc(sizeof(t_transform));
	ret->position = V3F_ZERO;
	ret->rotation = V3F_ZERO;
	ret->scale = V3F_ONE;
	ret->parent = NULL;
	ret->childs = list_new();
	ret->is_dirty = TRUE;
	return (ret);
}

t_transform	*trs_new(t_vector3f pos, t_vector3f rot, t_vector3f scale)
{
	t_transform *ret;

	ret = (t_transform *)malloc(sizeof(t_transform));
	ret->position = pos;
	ret->rotation = rot;
	ret->scale = scale;
	ret->parent = NULL;
	ret->childs = list_new();
	ret->is_dirty = TRUE;
	return (ret);
}

void		trs_set_dirty(t_transform *trs)
{
	trs->is_dirty = TRUE;
	list_process_inner(trs->childs, (void (*)(void *))trs_set_dirty);
}

t_matrix4f	*trs_get_matrix(t_transform *trs)
{
	if (trs->is_dirty)
		trs_recalculate_matrix(trs);
	return (&trs->model_world_matrix);
}

void		trs_set_child(t_transform *parent, t_transform *child)
{
	list_push_back(parent->childs, child);
	child->parent = parent;
	trs_set_dirty(child);
}

t_transform	*trs_get_child(t_transform *parent, int child_index)
{
	return (list_get_data_at(parent->childs, child_index));
}

void		trs_recalculate_matrix(t_transform *trs)
{
	t_matrix4f translation_matrix;
	t_matrix4f rotation_matrix;
	t_matrix4f scale_matrix;
	t_matrix4f parent_matrix;

	m4f_translate(&translation_matrix, trs->position);
	m4f_rotate(&rotation_matrix, trs->rotation);
	m4f_scale(&scale_matrix, trs->scale);
	m4f_mul(&translation_matrix, m4f_mul(&rotation_matrix, &scale_matrix));
	if (trs->parent != NULL)
	{
		m4f_cpy(&parent_matrix, trs_get_matrix(trs->parent));
		m4f_mul(&parent_matrix, &translation_matrix);
		translation_matrix = parent_matrix;
	}
	trs->model_world_matrix = translation_matrix;
	trs->is_dirty = FALSE;
}

t_vector3f	trs_transform_direction(t_transform *trs, t_vector3f v)
{
	t_vector4f	transform;
	t_matrix4f	rotation_matrix;

	m4f_rotate(&rotation_matrix, trs->rotation);
	transform = m4f_mul_vector(&rotation_matrix, V4F_INIT(v.x, v.y, v.z, 1.0f));
	return (V3F_INIT(transform.x, transform.y, transform.z));
}
