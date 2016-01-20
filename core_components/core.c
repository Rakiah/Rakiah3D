/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 18:33:33 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_env		*env_init(void (*update)(t_env *),
			void (*postrender)(t_env *),
			int frame_rate)
{
	t_env	*env;

	if ((env = (t_env *)malloc(sizeof(t_env))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((env->mlx = mlx_init()) == NULL)
		error_exit("MLX INIT FAILED");
	if ((env->wins = ft_create_array(sizeof(t_window *))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	if ((env->loaders = ft_create_array(sizeof(t_loader *))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	env_add_loader(env, &load_obj, ft_strdup("obj"));
	env_add_loader(env, &load_ro, ft_strdup("ro"));
	env_add_loader(env, &load_bitmap, ft_strdup("bmp"));
	env_add_loader(env, &load_rs, ft_strdup("rs"));
	env->selected = NULL;
	env->target_framerate = frame_rate;
	env->update = update;
	env->postrender = postrender;
	env->data = NULL;
	env->delta_time = 1.0f;
	mlx_loop_hook(env->mlx, &internal_update, env);
	return (env);
}

void		env_add_loader(t_env *env, t_floader loader, char *extension)
{
	t_loader *to_push;

	if ((to_push = malloc(sizeof(t_loader))) == NULL)
		error_exit("MEMORY ALLOCATION FAILED");
	to_push->extension = extension;
	to_push->method = loader;
	ft_pushback_array(env->loaders, &to_push, sizeof(t_loader *));
}

void		env_start(t_env *mlx)
{
	mlx_loop(mlx->mlx);
}

void		env_render(t_env *core)
{
	size_t		i;
	t_object	*obj;

	i = 0;
	while (i < core->selected->objs->count)
	{
		obj = ((t_object **)core->selected->objs->array)[i];
		obj_draw(core, obj);
		i++;
	}
}
