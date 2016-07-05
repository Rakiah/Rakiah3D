/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/05 15:42:46 by Rakiah           ###   ########.fr       */
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
