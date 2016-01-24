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

t_texture		*tex_new(int width, int height)
{
	t_texture *ret;

	if ((ret = (t_texture *)malloc(sizeof(t_texture))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((ret->img = mlx_new_image(get_core()->mlx, width, height)) == NULL)
		error_exit("MLX NEW IMAGE FAILED");
	if ((ret->pixels = mlx_get_data_addr(ret->img,
					&ret->bytes_per_pixel,
					&ret->l_size,
					(int *)&ret->endian)) == NULL)
		error_exit("MLX GET DATA ADDR FAILED");
	ret->bytes_per_pixel /= 8;
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

int				tex_get_pixel(t_texture *tex, int x, int y)
{
	return (*((unsigned int *)(tex->pixels + ((y * tex->l_size) +
				(x * tex->bytes_per_pixel)))));
}
