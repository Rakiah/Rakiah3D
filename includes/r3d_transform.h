/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_transform.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 17:36:27 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 17:55:57 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_TRANSFORM_H
# define R3D_TRANSFORM_H

#include <r3d.h>

t_transform		*trs_new_init();
t_transform		*trs_new(t_vector3f p, t_vector3f r, t_vector3f s);
t_vector3f		trs_transform_direction(t_transform *trs, t_vector3f v);
t_matrix4f		*trs_get_matrix(t_transform *trs);
t_transform		*trs_get_child(t_transform *parent, int child_index);
void			trs_recalculate_matrix(t_transform *trs);
void			trs_set_dirty(t_transform *trs);
void			trs_set_child(t_transform *parent, t_transform *child);
void			trs_set_pos(t_transform *trs, t_vector3f new_pos);
void			trs_set_pos_x(t_transform *trs, float x);
void			trs_set_pos_y(t_transform *trs, float y);
void			trs_set_pos_z(t_transform *trs, float z);
void			trs_set_rot(t_transform *trs, t_vector3f new_rot);
void			trs_set_rot_x(t_transform *trs, float x);
void			trs_set_rot_y(t_transform *trs, float y);
void			trs_set_rot_z(t_transform *trs, float z);
void			trs_set_scale(t_transform *trs, t_vector3f new_scale);
void			trs_set_scale_x(t_transform *trs, float x);
void			trs_set_scale_y(t_transform *trs, float y);
void			trs_set_scale_z(t_transform *trs, float z);
void			trs_translate(t_transform *trs, t_vector3f new_pos);
void			trs_rotate(t_transform *trs, t_vector3f new_rot);
void			trs_scale(t_transform *trs, t_vector3f new_scale);

#endif
