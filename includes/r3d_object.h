/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_object.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:13:01 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 18:13:40 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_OBJECT_H
# define R3D_OBJECT_H

t_object	*obj_new_init();
t_object	*obj_new_init_mesh(t_mesh *mesh);
t_object	*obj_new(t_mesh *mesh, t_transform *trs);
void		obj_draw(t_object *obj);
void		obj_attach_behaviour(t_object *obj, t_behaviour *behav);

# endif
