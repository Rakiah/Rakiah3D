/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 04:55:55 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 17:07:25 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_vector2f	*get_mouse_pos(void)
{
	return (mouse_pos(0, 0, CMD_GET));
}

t_vector2f	*mouse_pos(int x, int y, t_input_cmd cmd)
{
	static int last_x = 0;
	static int last_y = 0;

	if (cmd == CMD_SET)
	{
		last_x = x;
		last_y = y;
		return (NULL);
	}
	else if (cmd == CMD_GET)
		return (v2f_new(last_x, last_y));
	return (NULL);
}
