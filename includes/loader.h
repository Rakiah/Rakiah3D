/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkabbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:30:11 by bkabbas           #+#    #+#             */
/*   Updated: 2016/01/18 17:30:45 by bkabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

typedef	struct s_obj_model	t_obj_model;
typedef struct s_obj_index	t_obj_index;

struct			s_obj_model
{
	int			count;
	int			component_count;
	t_list		*pos;
	t_list		*tex_coords;
	t_list		*normals;
	t_list		*index;
};
struct			s_obj_index
{
	int i[3];
};
t_obj_model		*obj_model_new(int fd);
t_loader		*find_loader(t_env *core, char *ext);

void			*load_obj(t_env *core, char *path);
void			*load_ro(t_env *core, char *path);
void			*load_bitmap(t_env *core, char *path);
void			*load_rs(t_env *core, char *path);
void			*load(t_env *core, char *path);

#endif
