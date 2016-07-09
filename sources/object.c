/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 19:30:24 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_object	*obj_new_init(void)
{
	t_object *ret;

	ret = (t_object *)malloc(sizeof(t_object));
	ret->transform = trs_new_init();
	ret->behaviours = list_new();
	ret->mesh = mesh_new_init();
	ret->active = TRUE;
	list_push_back(get_core()->objects, ret);
	return (ret);
}

t_object	*obj_new_init_mesh(t_mesh *mesh)
{
	t_object *ret;

	ret = (t_object *)malloc(sizeof(t_object));
	ret->transform = trs_new_init();
	ret->behaviours = list_new();
	ret->active = TRUE;
	ret->mesh = mesh;
	list_push_back(get_core()->objects, ret);
	return (ret);
}

t_object	*obj_new(t_mesh *mesh, t_transform *trs)
{
	t_object *ret;

	ret = (t_object *)malloc(sizeof(t_object));
	ret->transform = trs;
	ret->behaviours = list_new();
	ret->active = TRUE;
	ret->mesh = mesh;
	list_push_back(get_core()->objects, ret);
	return (ret);
}

void		obj_attach_behaviour(t_object *obj, t_behaviour *behaviour)
{
	list_push_back(obj->behaviours, behaviour);
	if (behaviour->init != NULL)
		behaviour->init(obj, &behaviour->data);
	behaviour->active = TRUE;
	if (behaviour->start != NULL)
		behaviour->start(obj, behaviour->data);
}

void		obj_draw(t_object *obj)
{
	if (obj->mesh != NULL && obj->active != FALSE)
		mesh_draw(obj->mesh, obj->transform);
}
