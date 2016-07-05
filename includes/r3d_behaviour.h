/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_behaviour.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:13:47 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 18:15:13 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_BEHAVIOUR_H
# define R3D_BEHAVIOUR_H

void			behaviour_update(t_list *obj);
t_behaviour		*behaviour_new(void (*init)(t_object *, void **),
								void (*start)(t_object *, void *),
								void (*update)(t_object *, void *));

#endif
