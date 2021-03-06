/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/09 19:09:45 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_core		*get_core(void)
{
	static t_core	core;

	return (&core);
}

void		core_init(void (*update)(), int width, int height, int frame_rate)
{
	t_core	*core;

	core = get_core();
	pornygonz_init();
	pornygonz_create_window(width, height);
	pornygonz_enable_vertex_attribute(PORNYGONZ_DEPTH_BUFFER);
	core->loaders = list_new();
	core->cams = list_new();
	core->objects = list_new();
	core->resources = list_new();
	core_add_loader(load_obj, "obj");
	core_add_loader(load_ro, "ro");
	core_add_loader(load_bmp, "bmp");
	core_add_loader(load_3bmp, "3bmp");
	core_add_loader(load_rs, "rs");
	resources_load();
	core->width = width;
	core->height = height;
	core->shown_cursor = FALSE;
	core->locked_cursor = FALSE;
	core->update = update;
	core->camera = NULL;
	core->target_framerate = frame_rate;
	core->delta_time = 1.0f;
}

void		core_start(void)
{
	while (42)
		internal_update(get_core());
}

void		core_render(void)
{
	list_process_inner(get_core()->objects, (void (*)(void *))obj_draw);
}
