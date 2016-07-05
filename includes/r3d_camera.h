/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_camera.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:11:52 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 18:12:47 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_CAMERA_H
# define R3D_CAMERA_H

t_camera	*camera_new_init();
t_camera	*camera_new(t_projection_type type, t_transform *transform);
t_matrix4f	*camera_get_matrix(t_camera *camera);
void		camera_set_projection(t_camera *camera, t_projection_type proj);
void		camera_recalculate_matrix(t_camera *camera);

#endif
