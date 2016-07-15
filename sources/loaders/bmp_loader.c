/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/15 12:10:13 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <stdio.h>

static unsigned int			endian_read_int(FILE *file)
{
	unsigned char	b[4];
	unsigned int	i;

	if (fread(b, 1, 4, file) < 4)
		error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");
	i = (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0];
	return (i);
}

static unsigned short int	endian_read_short(FILE *file)
{
	unsigned char	b[2];
	unsigned short	s;

	if (fread(b, 1, 2, file) < 2)
		error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");
	s = (b[1] << 8) | b[0];
	return (s);
}

static t_texture			*create_image(FILE *file)
{
	int bounds[2];

	fseek(file, 18, SEEK_CUR);
	if (!(bounds[0] = endian_read_int(file)))
		error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");
	if (!(bounds[1] = endian_read_int(file)))
		error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");
	if (endian_read_short(file) != 1)
		error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");
	if (endian_read_short(file) != 24)
		error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");
	fseek(file, 24, SEEK_CUR);
	return (tex_new(bounds[0], bounds[1], 3));
}

void						*load_3bmp(char *path)
{
	t_texture		*image;
	FILE			*file;
	char			*tmp;
	int				i;
	int				j;

	if ((file = fopen(path, "rb")) == NULL)
		error_exit(rstd_strjoin("COULDN'T FIND FILE AT : ", path));
	image = create_image(file);
	if ((tmp = malloc(image->size)) && (fread(tmp, image->size, 1, file)) != 1)
		error_exit("BITMAP FILE NOT FORMATTED CORRECTLY");
	i = 0;
	j = 0;
	while (i < image->size)
	{
		((unsigned char *)image->pixels)[j + 0] = tmp[i + 0];
		((unsigned char *)image->pixels)[j + 1] = tmp[i + 1];
		((unsigned char *)image->pixels)[j + 2] = tmp[i + 2];
		i += 3;
		j += image->bytes_per_pixel;
	}
	free(tmp);
	pornygonz_bind_texture(image->tbo);
	pornygonz_add_texture_data(image->pixels, image->size);
	return (image);
}

void						*load_bmp(char *path)
{
	SDL_Surface		*s;
	t_texture		*image;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if ((s = SDL_LoadBMP(path)) == NULL)
		error_exit(rstd_strjoin("COULDN'T OPEN FILE AT : ", path));
	image = tex_new(s->w, s->h, s->format->BytesPerPixel);
	while (i < s->pitch * s->h)
	{
		((char *)image->pixels)[j + 0] = ((unsigned char *)s->pixels)[i + 0];
		((char *)image->pixels)[j + 1] = ((unsigned char *)s->pixels)[i + 1];
		((char *)image->pixels)[j + 2] = ((unsigned char *)s->pixels)[i + 2];
		i += s->format->BytesPerPixel;
		j += image->bytes_per_pixel;
	}
	SDL_FreeSurface(s);
	pornygonz_bind_texture(image->tbo);
	pornygonz_add_texture_data(image->pixels, image->size);
	return (image);
}
