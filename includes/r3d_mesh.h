/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_mesh.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:15:20 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 18:15:56 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_MESH_H
# define R3D_MESH_H

t_mesh	*mesh_new_init();
void	mesh_draw(t_mesh *mesh, t_transform *trs);
void	mesh_update_vertices(t_mesh *mesh);

#endif
