/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_behavior.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 06:14:15 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 16:30:48 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"
#include <time.h>

void	internal_render(t_env *mlx)
{
	size_t i;

	i = 0;
	while (i < mlx->wins->count)
	{
		mlx->selected = ((t_window **)mlx->wins->array)[i];
		if (!mlx->selected->cancel_render)
		{
			if (mlx->selected->cams->count > 0)
			{
				tex_clear(mlx->selected->screen_tex);
				clear_z_buffer(mlx->selected);
				env_render(mlx);
				mlx_put_image_to_window(mlx->mlx,
						mlx->selected->win,
						mlx->selected->screen_tex->img,
						0, 0);
			}
		}
		else
			mlx->selected->cancel_render = FALSE;
		i++;
	}
	if (mlx->wins->count > 0)
		mlx->selected = ((t_window **)mlx->wins->array)[0];
}

void	reset_inputs(void)
{
	key_up(-1, CMD_SET_ALL, FALSE);
	key_down(-1, CMD_SET_ALL, FALSE);
	mouse_up(-1, CMD_SET_ALL, FALSE);
	mouse_down(-1, CMD_SET_ALL, FALSE);
	focus_event(CMD_SET, FALSE);
}

void	calculate_delta_time(t_env *mlx, clock_t start)
{
	long		sleep_time;
	double		render_time;

	render_time = (double)(clock() - start) / CLOCKS_PER_SEC;
	sleep_time = ((((double)1 / mlx->target_framerate)
				- render_time) * 1000000);
	if (sleep_time >= 0)
	{
		mlx->delta_time = (double)sleep_time / 1000000;
		usleep(sleep_time);
	}
	else
		mlx->delta_time = 0;
	mlx->delta_time += (double)(clock() - start) / CLOCKS_PER_SEC;
}

int		internal_update(t_env *mlx)
{
	clock_t		start;

	start = clock();
	if (mlx->update != NULL)
		mlx->update(mlx);
	internal_render(mlx);
	if (mlx->postrender != NULL)
		mlx->postrender(mlx);
	reset_inputs();
	calculate_delta_time(mlx, start);
	return (0);
}
