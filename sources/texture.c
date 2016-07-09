/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/09 19:16:12 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_texture		*tex_new(int width, int height, int bpp)
{
	t_texture	*ret;

	ret = (t_texture *)malloc(sizeof(t_texture));
	ret->pixels = malloc(width * height * bpp);
	ret->bytes_per_pixel = bpp;
	ret->l_size = width * bpp;
	ret->width = width;
	ret->height = height;
	ret->size = ret->height * ret->l_size;
	ret->tbo = pornygonz_create_texture(width, height, bpp);
	return (ret);
}

void			tex_draw_pixel_index(t_texture *tex, int index, int pixel)
{
	*((unsigned int *)(tex->pixels + index)) = pixel;
}

void			tex_draw_pixel(t_texture *tex, int x, int y, int pixel)
{
	*((unsigned int *)(tex->pixels + ((y * tex->l_size) +
	(x * tex->bytes_per_pixel)))) = pixel;
}

int				tex_get_pixel(t_texture *tex, int x, int y)
{
	return (*((unsigned int *)(tex->pixels + ((y * tex->l_size) +
			(x * tex->bytes_per_pixel)))));
}
