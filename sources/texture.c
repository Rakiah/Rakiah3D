/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 19:30:06 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_texture		*tex_new(int width, int height)
{
	SDL_Surface *s;

	if ((s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0)) == NULL)
		error_exit(rstd_strjoin("SDL CREATE SURFACE FAILED", SDL_GetError()));
	return (tex_new_surface(width, height, s));
}

t_texture		*tex_new_surface(int w, int h, SDL_Surface *s)
{
	t_texture *ret;

	ret = (t_texture *)malloc(sizeof(t_texture));
	ret->pixels = s->pixels;
	ret->img = s;
	ret->width = w;
	ret->height = h;
	ret->tbo = pornygonz_create_texture(w, h);
	pornygonz_bind_texture(ret->tbo);
	pornygonz_add_texture_data(ret->pixels, w * h * s->format->BytesPerPixel);
	return (ret);
}
