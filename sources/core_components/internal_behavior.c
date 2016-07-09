/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_behavior.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:14:15 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 19:36:07 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <time.h>

void	internal_render(void)
{
	pornygonz_clear();
	core_render();
	pornygonz_swap_buffer();
}

void	internal_inputs(void)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			exit(0);
		else if (e.type == SDL_KEYDOWN)
			internal_key_down_hook(e.key.keysym.sym);
		else if (e.type == SDL_KEYUP)
			internal_key_up_hook(e.key.keysym.sym);
		else if (e.type == SDL_MOUSEMOTION)
		{
			internal_mouse_pos_hook(e.motion.x, e.motion.y);
			internal_mouse_motion_hook(e.motion.xrel, e.motion.yrel);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			internal_mouse_down_hook(e.button.button,
									e.button.x, e.button.y);
		else if (e.type == SDL_MOUSEBUTTONUP)
			internal_mouse_up_hook(e.button.button, e.button.x, e.button.y);
		else if (e.type == SDL_WINDOWEVENT)
			if (e.window.event == SDL_WINDOWEVENT_CLOSE)
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
