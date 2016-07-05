/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trs_operators_scale.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 05:32:15 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 15:42:28 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void		trs_scale(t_transform *trs, t_vector3f *new_scale)
{
	v3f_add(&trs->scale, new_scale);
	trs_set_dirty(trs);
}

void		trs_set_scale(t_transform *trs, t_vector3f *new_scale)
{
	trs->scale.x = new_scale->x;
	trs->scale.y = new_scale->y;
	trs->scale.z = new_scale->z;
	trs_set_dirty(trs);
}

void		trs_set_scale_x(t_transform *trs, float x)
{
	trs->scale.x = x;
	trs_set_dirty(trs);
}

void		trs_set_scale_y(t_transform *trs, float y)
{
	trs->scale.y = y;
	trs_set_dirty(trs);
}

void		trs_set_scale_z(t_transform *trs, float z)
{
	trs->scale.z = z;
	trs_set_dirty(trs);
}
