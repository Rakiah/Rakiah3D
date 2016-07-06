/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_behavior.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:14:15 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/06 18:54:22 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <time.h>

void	internal_render()
{
	pornygonz_clear();
	core_render();
	pornygonz_swap_buffer();
}

void	internal_inputs(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
		else if (event.type == SDL_KEYDOWN)
			internal_key_down_hook(event.key.keysym.sym);
		else if (event.type == SDL_KEYUP)
			internal_key_up_hook(event.key.keysym.sym);
		else if (event.type == SDL_MOUSEMOTION)
		{
			internal_mouse_pos_hook(event.motion.x, event.motion.y);
			internal_mouse_motion_hook(event.motion.xrel,
						event.motion.yrel);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			internal_mouse_down_hook(event.button.button,
						event.button.x,
						event.button.y);
		else if (event.type == SDL_MOUSEBUTTONUP)
			internal_mouse_up_hook(event.button.button,
						event.button.x,
						event.button.y);
		else if (event.type == SDL_WINDOWEVENT)
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				exit(0);
	}
}

void	reset_inputs(void)
{
	key_up(-1, CMD_SET_ALL, FALSE);
	mouse_up(-1, CMD_SET_ALL, FALSE);
}

void	calculate_delta_time(t_core *core, clock_t start)
{
	long		sleep_time;
	double		render_time;

	render_time = (double)(clock() - start) / CLOCKS_PER_SEC;
	sleep_time = ((((double)1 / core->target_framerate)
				- render_time) * 1000000);
	if (sleep_time > 0)
	{
		core->delta_time = (double)sleep_time / 1000000;
		usleep(sleep_time);
	}
	else
		core->delta_time = 0;
	core->delta_time += (double)(clock() - start) / CLOCKS_PER_SEC;
}

int		internal_update(t_core *core)
{
	clock_t		start;

	start = clock();
	internal_inputs();
	if (core->update != NULL)
		core->update();
	behaviour_update(core->objects);
	internal_render();
	reset_inputs();
	calculate_delta_time(core, start);
	return (0);
}
