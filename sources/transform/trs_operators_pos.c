/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trs_operators_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 05:29:08 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 17:41:14 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void		trs_translate(t_transform *trs, t_vector3f new_pos)
{
	trs->position = v3f_add(trs->position, new_pos);
	trs_set_dirty(trs);
}

void		trs_set_pos(t_transform *trs, t_vector3f new_pos)
{
	trs->position = new_pos;
	trs_set_dirty(trs);
}

void		trs_set_pos_x(t_transform *trs, float x)
{
	trs->position.x = x;
	trs_set_dirty(trs);
}

void		trs_set_pos_y(t_transform *trs, float y)
{
	trs->position.y = y;
	trs_set_dirty(trs);
}

void		trs_set_pos_z(t_transform *trs, float z)
{
	trs->position.z = z;
	trs_set_dirty(trs);
}
