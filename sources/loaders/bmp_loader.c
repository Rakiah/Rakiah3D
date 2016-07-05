/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/03/23 16:08:09 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include "SDL_image.h"
#include <stdio.h>

void			*load_image(char *path)
{
	SDL_Surface	*s;

	if ((s = SDL_LoadBMP(path)) == NULL)
		error_exit(ft_strjoin(ft_strjoin("COULDN'T OPEN FILE AT : ", path), SDL_GetError()));
	return (tex_new_surface(s->w, s->h, s));
}
