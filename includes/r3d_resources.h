/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_resources.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:10:51 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/27 16:03:05 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_RESOURCES_H
# define R3D_RESOURCES_H

void			resources_load();
void			resources_add(char *name, char *path);
void			*resources_poll(t_resource *res);
void			*resources_find(char *name);

#endif
