/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trs_hierarchy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 19:42:02 by bkabbas           #+#    #+#             */
/*   Updated: 2016/07/07 19:42:51 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "r3d.h"

void		trs_set_dirty(t_transform *trs)
{
	trs->is_dirty = TRUE;
	list_process_inner(trs->childs, (void (*)(void *))trs_set_dirty);
}

void		trs_set_child(t_transform *parent, t_transform *child)
{
	list_push_back(parent->childs, child);
	child->parent = parent;
	trs_set_dirty(child);
}

t_transform	*trs_get_child(t_transform *parent, int child_index)
{
	return (list_get_data_at(parent->childs, child_index));
}
