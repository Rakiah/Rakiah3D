/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_core.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:09:56 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/05 18:24:54 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_CORE_H
# define R3D_CORE_H

t_core		*get_core(void);
t_window	*window_new(int x, int y, char *title);
void		core_init(void (*update)(), int width, int height, int fcap);
void		core_add_loader(t_floader loader, char *extension);
void		core_show_cursor(t_bool state);
void		core_lock_cursor(t_bool state);
void		clear_z_buffer(void);
void		core_start(void);
void		core_render(void);
int			internal_update(t_core *core);
int			internal_key_down_hook(int code);
int			internal_key_up_hook(int code);
int			internal_mouse_down_hook(int code, int x, int y);
int			internal_mouse_up_hook(int code, int x, int y);
int			internal_mouse_pos_hook(int x, int y);
int			internal_mouse_motion_hook(int x, int y);
void		error_exit(char *error);

#endif
