/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:32:28 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/25 15:23:30 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_window	*window_new(int x, int y, char *title)
{
	t_window	*ret;
	t_core		*core;

	core = get_core();
	if ((ret = (t_window *)malloc(sizeof(t_window))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((ret->win = SDL_CreateWindow(title,
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					x, y,
					SDL_WINDOW_SHOWN)) == NULL)
		error_exit(ft_strjoin("SDL NEW WINDOW FAILED ", SDL_GetError()));
	ret->objs = list_new(sizeof(t_object *));
	ret->cams = list_new(sizeof(t_window *));
	if ((ret->z_buffer = (float **)ft_create_tab(x, y, sizeof(float))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	ret->screen_tex = tex_new(x, y);
	m4f_screen_space(&ret->screen_matrix, x, y);
	list_push_back(core->wins, ret);
	ret->id = core->wins->count - 1;
	core_select_window(ret->id);
	ret->cancel_render = FALSE;
	ret->width = x;
	ret->height = y;
	clear_z_buffer(ret);
	return (ret);
}

t_window	*core_select_window(int id)
{
	t_window	*selected;
	t_core		*core;

	core = get_core();
	selected = list_get_data_at(core->wins, id);
	core->window = selected;
	core->window_id = id;
	return (selected);
}

void		clear_z_buffer(t_window *win)
{
	int	i;
	int	j;

	i = 0;
	while (i < win->width)
	{
		j = 0;
		while (j < win->height)
		{
			win->z_buffer[i][j] = 9999999999.0f;
			j++;
		}
		i++;
	}
}
