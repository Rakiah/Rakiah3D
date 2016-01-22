/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 18:32:28 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/22 12:04:31 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_window	*window_new(t_env *env, int x, int y, char *title)
{
	t_window *ret;

	if ((ret = (t_window *)malloc(sizeof(t_window))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((ret->win = mlx_new_window(env->mlx, x, y, title)) == NULL)
		error_exit("MLX NEW WINDOW FAILED");
	if ((ret->objs = ft_create_array(sizeof(t_object *))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((ret->cams = ft_create_array(sizeof(t_camera *))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((ret->z_buffer = (float **)ft_create_tab(x, y, sizeof(float))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	ret->screen_tex = tex_new(env, x, y);
	m4f_screen_space(&ret->screen_matrix, (float)x, (float)y);
	mlx_hook(ret->win, 2, (1L << 0), &internal_key_down_hook, env);
	mlx_hook(ret->win, 3, (1L << 1), &internal_key_up_hook, env);
	mlx_hook(ret->win, 4, (1L << 2), &internal_mouse_down_hook, env);
	mlx_hook(ret->win, 5, (1L << 3), &internal_mouse_up_hook, env);
	mlx_hook(ret->win, 6, (1L << 6), &internal_mouse_pos_hook, env);
	mlx_hook(ret->win, 12, (1L << 15), &internal_expose_hook, env);
	ret->cancel_render = FALSE;
	ret->width = x;
	ret->height = y;
	clear_z_buffer(ret);
	ft_pushback_array(env->wins, &ret, sizeof(t_window *));
	return (ret);
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
