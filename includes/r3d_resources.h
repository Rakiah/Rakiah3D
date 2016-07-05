/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_resources.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:10:51 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 18:11:38 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_RESOURCES_H
# define R3D_RESOURCES_H

void			resources_load();
void			resources_add(char *name, void *data);
void			*resources_find(char *name);

#endif
