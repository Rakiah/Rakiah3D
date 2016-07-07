/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 01:16:03 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_material	*mat_new(t_texture *tex, t_vs_callback vs, t_fs_callback fs)
{
	t_material *ret;

	ret = (t_material *)malloc(sizeof(t_material));
	ret->texture = tex;
	ret->vs = vs;
	ret->fs = fs;
	return (ret);
}

t_material	*mat_new_texture(t_texture *tex)
{
	return (mat_new(tex, default_vertex_shader, default_fragment_shader));
}

t_material	*mat_new_init(void)
{
	return (mat_new_texture(NULL));
}

void		default_vertex_shader(const float *in_vertex, float out_pos[4])
{
	size_t		matrix_size;
	t_matrix4f	*mvp;
	t_vector4f	position;

	mvp = pornygonz_get_uniform("MVP", &matrix_size);
	position = V4F_INIT(in_vertex[0], in_vertex[1], in_vertex[2], 1.0f);
	position = m4f_mul_vector(mvp, position);
	rstd_memcpy(out_pos, (void *)&position, sizeof(t_vector4f));
}

void		default_fragment_shader(const float *in, unsigned char out[4])
{
	pornygonz_get_texture_pixel(in[3], in[4], out);
}
