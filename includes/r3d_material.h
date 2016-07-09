/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_material.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:21:27 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/09 18:43:44 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_MATERIAL_H
# define R3D_MATERIAL_H

t_material	*mat_new(t_texture *tex, t_vs_callback vs, t_fs_callback fs);
t_material	*mat_new_texture(t_texture *tex);
t_material	*mat_new_init(void);
void		default_vertex_shader(const float *in, float out_pos[4]);
void		default_fragment_shader(const float *in, float out_col[4]);

#endif
