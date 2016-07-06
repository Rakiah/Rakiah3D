/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/06 20:55:25 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <stdio.h>

/*unsigned int				endian_read_int(FILE *file)*/
/*{*/
	/*unsigned char	b[4];*/
	/*unsigned int	i;*/

	/*if (fread(b, 1, 4, file) < 4)*/
		/*error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");*/
	/*i = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0];*/
	/*return (i);*/
/*}*/

/*static unsigned short int	endian_read_short(FILE *file)*/
/*{*/
	/*unsigned char	b[2];*/
	/*unsigned short	s;*/

	/*if (fread(b, 1, 2, file) < 2)*/
		/*error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");*/
	/*s = (b[1] << 8) | b[0];*/
	/*return (s);*/
/*}*/

/*static void		*create_image(FILE *file, int bounds[2])*/
/*{*/
	/*fseek(file, 18, SEEK_CUR);*/
	/*if (!(bounds[0] = endian_read_int(file)))*/
		/*error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");*/
	/*if (!(bounds[1] = endian_read_int(file)))*/
		/*error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");*/
	/*if (endian_read_short(file) != 1)*/
		/*error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");*/
	/*if (endian_read_short(file) != 24)*/
		/*error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");*/
	/*fseek(file, 24, SEEK_CUR);*/
	/*return (malloc(bounds[0] * bounds[1] * 3));*/
/*}*/

/*void			draw_pixel_index(void *pixels, int index, int pixel)*/
/*{*/
	/**((unsigned int *)(pixels + index)) = pixel;*/
/*}*/

/*int				create_pixel(unsigned char a,*/
							/*unsigned char r,*/
							/*unsigned char g,*/
							/*unsigned char b)*/
/*{*/
	/*return ((a << 24) | (r << 16) | (g << 8) | (b));*/
/*}*/

/*void			*load_image(char *path)*/
/*{*/
	/*FILE	*file;*/
	/*int		bounds[2];*/
	/*unsigned long size;*/
	/*unsigned long i;*/
	/*char	*tmp;*/
	/*void	*pixels;*/
	/*SDL_Surface *s;*/

	/*if ((file = fopen(path, "rb")) == NULL)*/
		/*error_exit(ft_strjoin("COULDN'T FIND FILE AT : ", path));*/
	/*pixels = create_image(file, bounds);*/
	/*size = bounds[0] * bounds[1] * 3;*/
	/*tmp = (char *)malloc(size);*/
	/*if ((i = fread(tmp, size, 1, file)) != 1)*/
		/*error_exit(ft_strjoin("BITMAP FILE NOT FORMATTED CORRECTLY : ", path));*/
	/*i = 0;*/
	/*while (i < size)*/
	/*{*/
		/*draw_pixel_index(pixels, i + (i / 3),*/
							/*create_pixel(0, tmp[i + 2], tmp[i + 1], tmp[i]));*/
		/*i += 3;*/
	/*}*/
	/*free(tmp);*/

	/*s = SDL_CreateRGBSurfaceFrom(pixels, bounds[0], bounds[1], 24, bounds[0] * 3, 0, 0, 0, 0);*/
	/*t_texture *tex = tex_new_surface(bounds[0], bounds[1], s);*/
	/*tex->pixels = pixels;*/
	/*tex->img->pixels = pixels;*/
	/*return (tex);*/
/*}*/

void			*load_image(char *path)
{
	SDL_Surface	*s;

	if ((s = SDL_LoadBMP(path)) == NULL)
		error_exit(ft_strjoin(ft_strjoin("COULDN'T OPEN FILE AT : ", path), SDL_GetError()));
	return (tex_new_surface(s->w, s->h, s));
}
