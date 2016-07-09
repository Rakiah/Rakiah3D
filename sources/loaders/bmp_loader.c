/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/09 19:06:52 by Rakiah           ###   ########.fr       */
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
	FILE			*file;
	unsigned long	size;
	unsigned long	i;
	char			*tmp;
	t_texture		*image;

	if ((file = fopen(path, "rb")) == NULL)
		error_exit(rstd_strjoin("COULDN'T FIND FILE AT : ", path));
	image = create_image(file);
	size = image->width * image->height * 3;
	tmp = (char *)malloc(size);
	if ((i = fread(tmp, size, 1, file)) != 1)
		error_exit(rstd_strjoin("BITMAP FILE NOT FORMATTED CORRECTLY : ", path));
	i = 0;
	int j = 0;
	while (i < size)
	{
		((unsigned char *)image->pixels)[j] = tmp[i];
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
	int size = 0;
	int i = 0;
	int j = 0;

	if ((s = SDL_LoadBMP(path)) == NULL)
		error_exit(rstd_strjoin(rstd_strjoin("COULDN'T OPEN FILE AT : ", path), SDL_GetError()));
	size = s->pitch * s->h;
	image = tex_new(s->w, s->h, s->format->BytesPerPixel);
	while (i < size)
	{
		((unsigned char *)image->pixels)[j] = ((unsigned char *)s->pixels)[i];
		((unsigned char *)image->pixels)[j + 1] = ((unsigned char *)s->pixels)[i + 1];
		((unsigned char *)image->pixels)[j + 2] = ((unsigned char *)s->pixels)[i + 2];
		i += s->format->BytesPerPixel;
		j += image->bytes_per_pixel;
	}
	pornygonz_bind_texture(image->tbo);
	pornygonz_add_texture_data(image->pixels, image->size);
	return (image);
}
