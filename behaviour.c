/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 02:33:47 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_behaviour *behaviour_new(void (*init)(t_object *, void **),
				void (*start)(t_object *, void *),
				void (*update)(t_object *, void *))
{
	t_behaviour *ret;

	if ((ret = malloc(sizeof(t_behaviour))) == NULL)
		error_exit("memory allocation failed");
	ret->init = init;
	ret->start = start;
	ret->update = update;
	ret->data = NULL;
	ret->active = FALSE;
	return (ret);
}

void	behaviour_update(t_list *obj)
{
	t_object	*iter_obj;
	t_behaviour	*iter_behav;

	list_set_start(obj);
	while ((iter_obj = list_next(obj)) != NULL)
	{
		list_set_start(iter_obj->behaviours);
		while ((iter_behav = list_next(iter_obj->behaviours)) != NULL)
		{
			if (iter_behav->update != NULL)
				iter_behav->update(iter_obj, iter_behav->data);
		}
	}
}
