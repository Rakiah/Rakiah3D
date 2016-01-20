/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   focus_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 04:52:29 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 17:50:30 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_bool		focus_event(t_input_cmd cmd, t_bool value)
{
	static t_bool	focus;

	if (cmd == CMD_SET)
		focus = value;
	else if (cmd == CMD_GET)
		return (focus);
	return (focus);
}

int			internal_expose_hook(void *mlx)
{
	(void)mlx;
	focus_event(CMD_SET, TRUE);
	return (0);
}

t_bool		get_focus_event(void)
{
	return (focus_event(CMD_GET, FALSE));
}
