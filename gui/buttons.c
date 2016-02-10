/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 16:59:45 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_button	*button_new(t_ui_element *img,
				char *text,
				t_button_callback c_up,
				void *data)
{
	t_button		*ret;
	SDL_Rect		font_pos;
	SDL_Surface		*font_surface;
	SDL_Color		color;

	color = (SDL_Color){ 0, 0, 0, 0 };
	if ((ret = malloc(sizeof(t_button))) == NULL)
		error_exit("memory allocation failed");
	list_push_back(get_core()->ui_renderer->buttons, ret);
	font_surface = TTF_RenderUTF8_Blended(get_core()->ui_renderer->font,
						text, color);
	font_pos = (SDL_Rect){ (img->rect.w / 2 - font_surface->w / 2),
				img->rect.h / 2 - font_surface->h / 2,
				0, 0 };
	SDL_BlitSurface(font_surface, NULL, img->texture->img, &font_pos);
	ret->font = font_surface;
	ret->on_click_up = c_up;
	ret->on_click_up_data = data;
	ret->on_click_down = NULL;
	ret->on_click_down_data = NULL;
	ret->on_mouse_hover = NULL;
	ret->on_mouse_hover_data = NULL;
	ret->drawable = img;
	ret->active = TRUE;
	return (ret);
}

t_button	*button_new_init(t_rect *rect, char *text,
				t_button_callback c_up, void *data)
{
	return (button_new(ui_elem_new_color
				(create_pixel(255, 170, 170, 170), rect),
				text,
				c_up,
				data));
}

void		button_bind_click_up(t_button *b,
					t_button_callback up,
					void *data)
{
	b->on_click_up = up;
	b->on_click_up_data = data;
}

void		button_bind_click_down(t_button *b,
					t_button_callback down,
					void *data)
{
	b->on_click_down = down;
	b->on_click_down_data = data;
}

void		button_bind_mouse_hover(t_button *b,
					t_button_callback hover,
					void *data)
{
	b->on_mouse_hover = hover;
	b->on_mouse_hover_data = data;
}
