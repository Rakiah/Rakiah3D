/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 02:33:47 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_object	*obj_new_init(t_window *win)
{
	t_object *ret;

	if ((ret = (t_object *)malloc(sizeof(t_object))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	ret->transform = trs_new_init();
	ret->behaviours = list_new(sizeof(t_behaviour *));
	ret->mesh = mesh_new_init();
	ret->active = TRUE;
	if (win != NULL)
		list_push_back(win->objs, ret);
	return (ret);
}

t_object	*obj_new_init_mesh(t_window *win, t_mesh *mesh)
{
	t_object *ret;

	if ((ret = (t_object *)malloc(sizeof(t_object))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	ret->transform = trs_new_init();
	ret->behaviours = list_new(sizeof(t_behaviour *));
	ret->active = TRUE;
	if (win != NULL)
		list_push_back(win->objs, ret);
	ret->mesh = mesh;
	return (ret);
}

t_object	*obj_new(t_window *win, t_mesh *mesh, t_transform *trs)
{
	t_object *ret;

	if ((ret = (t_object *)malloc(sizeof(t_object))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	ret->transform = trs;
	ret->behaviours = list_new(sizeof(t_behaviour *));
	ret->mesh = mesh;
	ret->active = TRUE;
	if (win != NULL)
		list_push_back(win->objs, ret);
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
