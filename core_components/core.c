/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/25 15:21:44 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_core		*get_core(void)
{
	static t_core	core;

	return (&core);
}

void		core_init(void (*update)(),
			void (*expose)(t_window *),
			void (*postrender)(),
			int frame_rate)
{
	t_core	*core;

	core = get_core();
	SDL_Init(SDL_INIT_VIDEO);
	if ((core->wins = ft_create_array(sizeof(t_window *))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((core->loaders = ft_create_array(sizeof(t_loader *))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	core_add_loader(&load_obj, ft_strdup("obj"));
	core_add_loader(&load_ro, ft_strdup("ro"));
	core_add_loader(&load_bitmap, ft_strdup("bmp"));
	core_add_loader(&load_rs, ft_strdup("rs"));
	core->ui_renderer = gui_init();
	core->shown_cursor = FALSE;
	core->locked_cursor = FALSE;
	core->update = update;
	core->postrender = postrender;
	core->expose = expose;
	core->window = NULL;
	core->data = NULL;
	core->window_id = -1;
	core->target_framerate = frame_rate;
	core->delta_time = 1.0f;
}

void		core_show_cursor(t_bool state)
{
	get_core()->shown_cursor = state;
	SDL_ShowCursor(state);
}

void		core_lock_cursor(t_bool state)
{
	get_core()->locked_cursor = state;
}

void		core_add_loader(t_floader loader, char *extension)
{
	t_loader	*to_push;
	t_core		*core;

	core = get_core();
	if ((to_push = malloc(sizeof(t_loader))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	to_push->extension = extension;
	to_push->method = loader;
	ft_pushback_array(core->loaders, &to_push, sizeof(t_loader *));
}

void		core_start(void)
{
	while (42)
		internal_update(get_core());
}

void		core_render(void)
{
	size_t		i;
	t_object	*obj;
	t_core		*core;

	core = get_core();
	i = 0;
	while (i < core->window->objs->count)
	{
		obj = ((t_object **)core->window->objs->array)[i];
		obj_draw(obj);
		i++;
	}
}
