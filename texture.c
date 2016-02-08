/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 17:58:18 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

int			**copy_pixels(SDL_Surface *s)
{
	int	**pixels;
	int	x;
	int	y;
	/*int	i;*/

	/*i = 0;*/
	x = 0;
	/*pixels = NULL;*/
	/*ft_putnbr(s->w);*/
	/*ft_putchar('\n');*/
	/*ft_putnbr(s->h);*/
	/*ft_putchar('\n');*/

	pixels = (int **)ft_create_tab(s->w, s->h, sizeof(int));
	/*while (i < s->*/
	while (x < s->w)
	{
		y = 0;
		while (y < s->h)
		{
			pixels[x][y] = *((unsigned int *)(s->pixels + ((y * s->pitch)
					+ (x * s->format->BytesPerPixel))));
	/*return (*((unsigned int *)(tex->pixels +*/
		/*((y * tex->l_size) + (x * tex->bytes_per_pixel)))));*/
			y++;
		}
		x++;
		/*i++;*/
	}
	return (pixels);
}

t_texture		*tex_new(int width, int height)
{
	t_texture *ret;
	SDL_Surface *s;

	if ((ret = (t_texture *)malloc(sizeof(t_texture))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0)) == NULL)
		error_exit(ft_strjoin("SDL CREATE SURFACE FAILED", SDL_GetError()));
	ret->fast_pixel_access = copy_pixels(s);
	ret->pixels = s->pixels;
	ret->bytes_per_pixel = s->format->BytesPerPixel;
	ret->l_size = s->pitch;
	ret->img = s;
	ret->width = width;
	ret->height = height;
	ret->size = ret->height * ret->l_size;
	return (ret);
}

t_texture		*tex_new_surface(int width, int height, SDL_Surface *s)
{
	t_texture *ret;

	if ((ret = (t_texture *)malloc(sizeof(t_texture))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	ret->fast_pixel_access = copy_pixels(s);
	ret->pixels = s->pixels;
	ret->bytes_per_pixel = s->format->BytesPerPixel;
	ret->l_size = s->pitch;
	ret->img = s;
	ret->width = width;
	ret->height = height;
	ret->size = ret->height * ret->l_size;
	return (ret);
}

void			tex_clear(t_texture *tex)
{
	ft_memset(tex->pixels, 0, tex->size);
}

void			tex_draw_pixel_index(t_texture *tex, int index, int pixel)
{
	*((unsigned int *)(tex->pixels + (index * tex->bytes_per_pixel))) = pixel;
}

void			tex_draw_pixel(t_texture *tex, int x, int y, int pixel)
{
	*((unsigned int *)(tex->pixels + ((y * tex->l_size) +
	(x * tex->bytes_per_pixel)))) = pixel;
}

int			tex_get_pixel(t_texture *tex, int x, int y)
{
	return (tex->fast_pixel_access[x][y]);
}
