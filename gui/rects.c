/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rects.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 16:59:45 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

t_rect	*rect_new(int posX, int posY, int sizeX, int sizeY)
{
	t_rect *ret;

	if ((ret = malloc(sizeof(t_rect))) == NULL)
		error_exit("memory allocation failed");
	ret->x = posX;
	ret->y = posY;
	ret->w = sizeX;
	ret->h = sizeY;
	return (ret);
}

t_rect	*rect_new_vectors(t_vector2f *pos, t_vector2f *size)
{
	return (rect_new(pos->x, pos->y, size->x, size->y));
}

t_bool	rect_contains(t_rect *rect, int x, int y)
{
	return ((x >= rect->x && x <= rect->x + rect->w) &&
		(y >= rect->y && y <= rect->y + rect->h));
}

t_bool	rect_intersects(t_rect *r1, t_rect *r2)
{
	return (rect_contains(r1, r2->x, r2->y) ||
		rect_contains(r1, r2->x + r2->w, r2->y + r2->y));
}
