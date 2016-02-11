/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m4f_initializers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 04:22:13 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 04:28:46 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void		m4f_translate(t_matrix4f *matrix, t_vector3f t)
{
	m4f_identity(matrix);
	matrix->m[0][3] = t.x;
	matrix->m[1][3] = t.y;
	matrix->m[2][3] = t.z;
}

void		m4f_scale(t_matrix4f *matrix, t_vector3f s)
{
	m4f_identity(matrix);
	matrix->m[0][0] = s.x;
	matrix->m[1][1] = s.y;
	matrix->m[2][2] = s.z;
}

void		m4f_rotate(t_matrix4f *matrix, t_vector3f r)
{
	t_matrix4f rx;
	t_matrix4f ry;
	t_matrix4f rz;

	r.x = r.x * ft_pi() / 180.0f;
	r.y = r.y * ft_pi() / 180.0f;
	r.z = r.z * ft_pi() / 180.0f;
	m4f_identity(&rx);
	m4f_identity(&ry);
	m4f_identity(&rz);
	rx.m[1][1] = (float)cos(r.x);
	rx.m[1][2] = -(float)sin(r.x);
	rx.m[2][1] = (float)sin(r.x);
	rx.m[2][2] = (float)cos(r.x);
	ry.m[0][0] = (float)cos(r.y);
	ry.m[0][2] = (float)sin(r.y);
	ry.m[2][0] = -(float)sin(r.y);
	ry.m[2][2] = (float)cos(r.y);
	rz.m[0][0] = (float)cos(r.z);
	rz.m[0][1] = -(float)sin(r.z);
	rz.m[1][0] = (float)sin(r.z);
	rz.m[1][1] = (float)cos(r.z);
	m4f_cpy(matrix, m4f_mul(&rz, m4f_mul(&ry, &rx)));
}

void		m4f_perspective(t_camera *camera)
{
	float	fov_rad;
	float	fov;
	float	zrange;
	float	ar;

	fov_rad = camera->fov * (ft_pi() / 180.0f);
	fov = (float)tan(fov_rad * 0.5f);
	zrange = camera->z_bounds.x - camera->z_bounds.y;
	ar = camera->size.x / camera->size.y;
	m4f_identity(&camera->projection);
	camera->projection.m[0][0] = 1.0f / (fov * ar);
	camera->projection.m[1][1] = 1.0f / fov;
	camera->projection.m[2][2] = (-camera->z_bounds.x -
									camera->z_bounds.y) / zrange;
	camera->projection.m[2][3] = 2 * camera->z_bounds.y *
									camera->z_bounds.x / zrange;
	camera->projection.m[3][2] = 1;
	camera->projection.m[3][3] = 0;
}

void		m4f_screen_space(t_matrix4f *m, float width, float height)
{
	m4f_identity(m);
	m->m[0][0] = width / 2;
	m->m[0][3] = (width / 2);
	m->m[1][1] = -(height / 2);
	m->m[1][3] = (height / 2);
	m->m[3][3] = 1;
}
