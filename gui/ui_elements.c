/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_elements.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 16:59:45 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_ui_element	*ui_elem_new(t_texture *tex, t_rect *rect)
{
	t_ui_element	*ret;

	if ((ret = malloc(sizeof(t_ui_element))) == NULL)
		error_exit("malloc failed");
	ret->texture = tex_new(rect->w, rect->h);
	SDL_BlitScaled(tex->img, NULL, ret->texture->img, NULL);
	ret->rect = *rect;
	ret->active = TRUE;
	list_push_back(get_core()->ui_renderer->elements, ret);
	return (ret);
}

t_ui_element	*ui_elem_new_color(int color, t_rect *rect)
{
	t_ui_element	*ret;
	int		i;
	int		real_size;

	if ((ret = malloc(sizeof(t_ui_element))) == NULL)
		error_exit("malloc failed");
	ret->texture = tex_new(rect->w, rect->h);
	ret->rect = *rect;
	ret->active = TRUE;
	i = 0;
	real_size = ret->texture->size / ret->texture->bytes_per_pixel;
	while (i < real_size)
	{
		tex_draw_pixel_index(ret->texture, i, color);
		i++;
	}
	list_push_back(get_core()->ui_renderer->elements, ret);
	return (ret);
}

void		ui_elem_draw(t_ui_element *elem)
{
	if (!elem->active)
		return ;
	SDL_BlitSurface(elem->texture->img, NULL,
			get_core()->window->screen_tex->img,
			(SDL_Rect *)&elem->rect);
}
