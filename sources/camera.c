/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 15:43:56 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_camera	*camera_new_init()
{
	t_camera *ret;
	t_core	*core;

	core = get_core();
	ret = (t_camera *)malloc(sizeof(t_camera));
	ret->transform = trs_new_init();
	ret->fov = 60;
	ret->z_bounds.x = 0.01f;
	ret->z_bounds.y = 1000.0f;
	ret->size.x = core->width;
	ret->size.y = core->height;
	ret->is_dirty = TRUE;
	m4f_perspective(&ret->projection, ret->fov, ret->size, ret->z_bounds);
	list_push_back(core->cams, ret);
	core->camera = ret;
	return (ret);
}

t_camera	*camera_new(t_projection_type project, t_transform *transform)
{
	t_camera *ret;
	t_core	*core;

	core = get_core();
	ret = (t_camera *)malloc(sizeof(t_camera));
	ret->transform = transform;
	ret->fov = 60;
	ret->z_bounds.x = 0.01f;
	ret->z_bounds.y = 1000.0f;
	ret->size.x = core->width;
	ret->size.y = core->height;
	ret->is_dirty = TRUE;
	if (project == PERSPECTIVE)
		m4f_perspective(&ret->projection, ret->fov, ret->size, ret->z_bounds);
	else
		m4f_identity(&ret->projection);
	list_push_back(core->cams, ret);
	core->camera = ret;
	return (ret);
}

void		camera_set_projection(t_camera *c, t_projection_type p)
{
	if (p == PERSPECTIVE)
		m4f_perspective(&c->projection, c->fov, c->size, c->z_bounds);
	else
		m4f_identity(&c->projection);
	c->project_type = p;
	c->is_dirty = TRUE;
}

t_matrix4f	*camera_get_matrix(t_camera *camera)
{
	if (camera->is_dirty || camera->transform->is_dirty)
		camera_recalculate_matrix(camera);
	return (&camera->projected_view);
}

void		camera_recalculate_matrix(t_camera *camera)
{
	t_matrix4f inverted;
	t_matrix4f projection;

	m4f_cpy(&projection, &camera->projection);
	m4f_invert(m4f_cpy(&inverted, trs_get_matrix(camera->transform)));
	m4f_cpy(&camera->projected_view, m4f_mul(&projection, &inverted));
	camera->is_dirty = FALSE;
}
