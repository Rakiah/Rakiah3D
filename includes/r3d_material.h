/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_material.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:21:27 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 18:21:50 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_MATERIAL_H
# define R3D_MATERIAL_H

t_material		*mat_new(t_texture *tex, t_vs_callback vs, t_fs_callback fs);

#endif
