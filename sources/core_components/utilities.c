/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 19:32:09 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 19:32:45 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

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

	to_push = malloc(sizeof(t_loader));
	to_push->extension = rstd_strdup(extension);
	to_push->method = loader;
	list_push_back(get_core()->loaders, to_push);
}
