/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trs_operators_rot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 05:30:43 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 15:41:44 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void		trs_rotate(t_transform *trs, t_vector3f *new_rot)
{
	v3f_add(&trs->rotation, new_rot);
	trs->rotation.x = lroundf(trs->rotation.x) % 360;
	trs->rotation.y = lroundf(trs->rotation.y) % 360;
	trs->rotation.z = lroundf(trs->rotation.z) % 360;
	trs_set_dirty(trs);
}

void		trs_set_rot(t_transform *trs, t_vector3f *new_rot)
{
	trs->rotation.x = lroundf(new_rot->x) % 360;
	trs->rotation.y = lroundf(new_rot->y) % 360;
	trs->rotation.z = lroundf(new_rot->z) % 360;
	trs_set_dirty(trs);
}

void		trs_set_rot_x(t_transform *trs, float x)
{
	trs->rotation.x = lroundf(x) % 360;
	trs_set_dirty(trs);
}

void		trs_set_rot_y(t_transform *trs, float y)
{
	trs->rotation.y = lroundf(y) % 360;
	trs_set_dirty(trs);
}

void		trs_set_rot_z(t_transform *trs, float z)
{
	trs->rotation.z = lroundf(z) % 360;
	trs_set_dirty(trs);
}
