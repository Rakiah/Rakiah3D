/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 16:59:45 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_interface_renderer	*gui_init(void)
{
	t_interface_renderer *renderer;

	if (TTF_Init() == -1)
		error_exit("couldnt init TTF");
	if ((renderer = malloc(sizeof(t_interface_renderer))) == NULL)
		error_exit("malloc failed");
	renderer->buttons = list_new(sizeof(t_button *));
	renderer->elements = list_new(sizeof(t_ui_element *));
	renderer->font = TTF_OpenFont("resources/font.ttf", 20);
	if (renderer->font == NULL)
		error_exit("couldnt file font to be loaded");
	return (renderer);
}

static void		gui_poll_events_inner(t_button *button,
					t_vector2f mouse_pos)
{
	if (!button->active)
		return ;
	if (rect_contains(&button->drawable->rect, mouse_pos.x, mouse_pos.y))
	{
		if ((get_mouse_button_up(0) || get_mouse_button_up(1)))
		{
			if (button->on_click_up != NULL)
				button->on_click_up(button,
				button->on_click_up_data);
		}
		else if (get_mouse_button_down(0) || get_mouse_button_down(1))
		{
			if (button->on_click_down != NULL)
				button->on_click_down(button,
				button->on_click_down_data);
		}
		else
		{
			if (button->on_mouse_hover != NULL)
				button->on_mouse_hover(button,
				button->on_mouse_hover_data);
		}
	}
}

void			gui_poll_events(t_interface_renderer *interface)
{
	t_list *buttons;
	t_button *iterator;
	t_vector2f mouse_pos;

	buttons = interface->buttons;
	mouse_pos = get_mouse_pos();
	list_set_start(buttons);
	while ((iterator = list_next(buttons)) != NULL)
		gui_poll_events_inner(iterator, mouse_pos);
}
