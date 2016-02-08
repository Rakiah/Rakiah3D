/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_behavior.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:14:15 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/25 15:24:26 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <time.h>

static void	draw(t_window *win)
{
	if (win->cancel_render)
	{
		win->cancel_render = FALSE;
		return ;
	}
	if (win->cams->count == 0)
		return ;
	tex_clear(win->screen_tex);
	clear_z_buffer(win);
	core_render(get_core());
	SDL_BlitSurface(win->screen_tex->img, NULL,
			SDL_GetWindowSurface(win->win), NULL);
	SDL_UpdateWindowSurface(win->win);
}

void	internal_render(t_core *core)
{
	size_t		i;
	int		selected;

	if ((selected = core->window_id) == -1)
		return ;
	i = 0;
	while (i < core->wins->count)
	{
		core_select_window(i);
		draw(core->window);
		i++;
	}
	core_select_window(selected);
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

int		internal_expose_hook(t_window *window)
{
	t_core *core;

	core = get_core();
	if (core->expose != NULL)
		core->expose(window);
	return (0);
}

int		internal_update(t_core *core)
{
	clock_t		start;

	start = clock();
	internal_inputs();
	if (core->update != NULL)
		core->update();
	internal_render(core);
	if (core->postrender != NULL)
		core->postrender();
	if (core->locked_cursor)
		SDL_WarpMouseInWindow(core->window->win,
				core->window->width / 2,
				core->window->height / 2);
	reset_inputs();
	calculate_delta_time(core, start);
	return (0);
}
