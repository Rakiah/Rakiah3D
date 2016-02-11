/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_gui.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 02:33:32 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/13 16:59:45 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_GUI_H
# define R3D_GUI_H

t_button		*button_new(t_ui_element *img,
					char *text,
					t_button_callback c_up,
					void *data);
t_button		*button_new_init(t_rect *rect,
					char *text,
					t_button_callback c_up,
					void *data);
void			button_bind_click_up(t_button *b,
						t_button_callback up,
						void *data);
void			button_bind_mouse_hover(t_button *b,
						t_button_callback hover,
						void *data);
void			button_bind_click_down(t_button *b,
						t_button_callback down,
						void *data);
t_rect			*rect_new(int posX, int posY, int sizeX, int sizeY);
t_rect			*rect_new_vectors(t_vector2f *pos, t_vector2f *size);
t_bool			rect_contains(t_rect *rect, int x, int y);
t_bool			rect_intersects(t_rect *r1, t_rect *r2);
t_ui_element		*ui_elem_new(t_texture *tex, t_rect *rect);
t_ui_element		*ui_elem_new_color(int color, t_rect *rect);
void			ui_elem_draw(t_ui_element *elem);
t_interface_renderer	*gui_init(void);
void			gui_poll_events(t_interface_renderer *interface);


#endif
