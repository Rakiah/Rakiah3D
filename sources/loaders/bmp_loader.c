/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 19:45:49 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void			*load_image(char *path)
{
	SDL_Surface	*s;

	if ((s = SDL_LoadBMP(path)) == NULL)
		error_exit(rstd_strjoin("COULDN'T OPEN FILE AT : ", path));
	return (tex_new_surface(s->w, s->h, s));
}
