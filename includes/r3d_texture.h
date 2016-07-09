/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r3d_texture.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rakiah <bkabbas@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 18:16:25 by Rakiah            #+#    #+#             */
/*   Updated: 2016/07/09 18:11:40 by Rakiah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef R3D_TEXTURE_H
# define R3D_TEXTURE_H

t_texture	*tex_new(int width, int height, int bytes_per_pixel);
t_texture	*tex_new_surface(int width, int height, SDL_Surface *s);
void		tex_clear(t_texture *tex);
void		tex_draw_pixel(t_texture *tex, int x, int y, int pixel);
void		tex_draw_pixel_index(t_texture *tex, int index, int pixel);
void		tex_to_screen(t_texture *tex, t_core *core);
int			tex_get_pixel(t_texture *tex, int x, int y);

#endif
